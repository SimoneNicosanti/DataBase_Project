#include "TablePrinterHeader.h"

int findColMaxSize(void ***table, char **headerArray, int rowsNum, int colIndex, enum TableFieldType colType) {
    int maxSize = strlen(headerArray[colIndex]) ;

    for (int rowIndex = 0 ; rowIndex < rowsNum ; rowIndex++) {
        void *currentElem = table[rowIndex][colIndex] ;

        int currentSize ;
        char intBuff[50] ;
        switch (colType) {
            case STRING :
                currentSize = strlen((char *) currentElem) ;
                break ;
            case INT :
                sprintf(intBuff, "%d", *((int *)currentElem)) ;
                currentSize = strlen(intBuff) ;
                break ;
            case DATE : 
                currentSize = strlen("yyyy-mm-dd") ;
                break ;
            case TIME :
                currentSize = strlen("hh:mm") ;
                break ;
        }

        if (maxSize < currentSize) maxSize = currentSize ;
    }

    return maxSize ;
}

void printSeparator(int *widthArray, int colNum) {
    putchar('+') ;
    for (int colIndex = 0 ; colIndex < colNum ; colIndex++) {
        for (int i = 0 ; i < widthArray[colIndex] ; i++) putchar('-') ;
        putchar('+') ;
    }
    putchar('\n') ;
}

void printHeader(char **headerArray, int *widthArray, int colsNum) {
    putchar('|') ;
    for (int colIndex = 0 ; colIndex < colsNum ; colIndex++) {
            printf(" %-*s", widthArray[colIndex] - 1, headerArray[colIndex]) ;
            putchar('|') ;
        }
    putchar('\n') ;
}

void printRow(void ***table, int rowIndex, int colNum, int *widthArray, enum TableFieldType *rowStruct) {
    putchar('|') ;

    char dateBuff[50] ;
    char timeBuff[50] ;
    Date *datePtr ;
    Time *timePtr ;
    for (int colIndex = 0 ; colIndex < colNum ; colIndex++) {
        void *currentElem = table[rowIndex][colIndex] ;
        enum TableFieldType currentType = rowStruct[colIndex] ;
        int fieldSize = widthArray[colIndex] - 1 ;

        switch (currentType) {
            case STRING :
                printf(" %-*s", fieldSize, (char *) currentElem) ;
                break ;
            case INT :
                printf(" %-*d", fieldSize, *((int *) currentElem)) ;
                break; ;
            case DATE :
                datePtr = (Date *) currentElem ;
                sprintf(dateBuff, "%d-%02d-%02d", datePtr->year, datePtr->month, datePtr->day) ;
                printf(" %-*s", fieldSize, dateBuff) ;
                break ;
            case TIME :
                timePtr = (Time *) currentElem ;
                sprintf(timeBuff, "%02d:%02d", timePtr->hour, timePtr->minute) ;
                printf(" %-*s", fieldSize, timeBuff) ;
                break ;
        }
        //Usato -1 per inserire lo spazio aggiuntivo a dx e dare più visibilità all'output
        putchar('|') ;
        
    }
    putchar('\n') ;
}


void printTable(Table *tablePtr) {

    int rowsNum = tablePtr->rowsNum ;
    int colsNum = tablePtr->colsNum ;
    char **headerArray = tablePtr->headerArray ;
    enum TableFieldType *rowTypes = tablePtr->rowStruct ;

    void ***table = tablePtr->table ;

    int maxWidthArray[colsNum] ;
    
    for (int colIndex = 0 ; colIndex < colsNum ; colIndex++) {
        int colMaxSize = findColMaxSize(table, headerArray, rowsNum, colIndex, rowTypes[colIndex]) ;
        maxWidthArray[colIndex] = 5 + colMaxSize ;
    }

    printSeparator(maxWidthArray, colsNum) ;
    printHeader(headerArray, maxWidthArray, colsNum) ;

    for (int rowIndex = 0 ; rowIndex < rowsNum ; rowIndex++) {
        printSeparator(maxWidthArray, colsNum) ;
        printRow(table, rowIndex, colsNum, maxWidthArray, rowTypes) ;
    }
    printSeparator(maxWidthArray, colsNum) ;
}


Table *createTable(int rowsNum, int colsNum, char **headerArray, enum TableFieldType *rowTypes) {

    Table *tablePtr = malloc(sizeof(Table)) ;
    if (tablePtr == NULL) exit(-1) ;

    tablePtr->table = (void ***) malloc(sizeof(void **) * rowsNum) ;
    if (tablePtr->table == NULL) exit(-1) ;

    for (int rowIndex = 0 ; rowIndex < rowsNum ; rowIndex++) {
        tablePtr->table[rowIndex] = (void **) malloc(sizeof(void *) * colsNum) ;
        if (tablePtr->table[rowIndex] == NULL) exit(-1) ;
    }

    tablePtr->colsNum = colsNum ;
    tablePtr->rowsNum = rowsNum ;
    tablePtr->headerArray = headerArray ;
    tablePtr->rowStruct = rowTypes ;

    return tablePtr ;
}

void freeTable(Table *tablePtr) {

    for (int rowIndex = 0 ; rowIndex < tablePtr->rowsNum ; rowIndex++) {
        free(tablePtr->table[rowIndex]) ;
    }

    free(tablePtr) ;
}

void setTableElem(Table *tablePtr, int rowIndex, int colIndex, void *elemPtr) {
    (tablePtr->table)[rowIndex][colIndex] = elemPtr ;
}