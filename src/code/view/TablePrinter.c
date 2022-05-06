#include "TablePrinterHeader.h"


int findColWidth(Table *tablePtr, int colIndex) {
    char *header = tablePtr->headerArray[colIndex] ;
    int maxWidth = strlen(header) ;
    
    for (int rowIndex = 0 ; rowIndex < tablePtr->rowsNum ; rowIndex++) {
        char *currentString = (tablePtr->tableRows)[rowIndex][colIndex] ;
        int currentSize = strlen(currentString) ;
        if (maxWidth < currentSize) {
            maxWidth = currentSize ;
        }
    }

    return maxWidth ;
}


void printSeparator(int *widthArray, int colNum) {
    putchar('+') ;
    for (int colIndex = 0 ; colIndex < colNum ; colIndex++) {
        for (int i = 0 ; i < widthArray[colIndex] ; i++) putchar('-') ;
        putchar('+') ;
    }
    putchar('\n') ;
}

void printRow(int *widthArray, char **row, int colNum) {
    putchar('|') ;
    for (int colIndex = 0 ; colIndex < colNum ; colIndex++) {
        //Usato -1 per inserire lo spazio aggiuntivo a dx e dare più visibilità all'output
        printf(" %-*s", widthArray[colIndex] - 1, row[colIndex]) ;
        
        putchar('|') ;
    }
    putchar('\n') ;
}


void printTable(Table *tablePtr) {
    
    int maxWidthArray[tablePtr->colsNum] ;
    
    for (int colIndex = 0 ; colIndex < tablePtr->colsNum ; colIndex++) {
        maxWidthArray[colIndex] = 7 + findColWidth(tablePtr, colIndex) ;
    }

    printSeparator(maxWidthArray, tablePtr->colsNum) ;
    printRow(maxWidthArray, tablePtr->headerArray, tablePtr->colsNum) ;

    for (int rowIndex = 0 ; rowIndex < tablePtr->rowsNum ; rowIndex++) {
        printSeparator(maxWidthArray, tablePtr->colsNum) ;
        printRow(maxWidthArray, tablePtr->tableRows[rowIndex], tablePtr->colsNum) ;
    }
    printSeparator(maxWidthArray, tablePtr->colsNum) ;
}