#include "Test.h"

void test1() {
    char *headerArray[] = {"Header 1","Header 2", "Header 3"} ;
    enum TableFieldType rowTypes[] = {STRING, STRING, STRING} ;
    Table *testTable = createTable(2, 3, headerArray, rowTypes) ;

    char *testStrings[2][3] = {
        {"Ciao a Tutti", "Come State", "Tutto Bene"},
        {"Alla Vita", "Non viene concesso in sorte", "Di riveder se stessa nella morte"} 
    } ;

    for (int i = 0 ; i < 2 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
            setTableElem(testTable, i, j, testStrings[i][j]) ;
        }
    }
    printTable(testTable) ;
}

void test2() {
    char *headerArray[] = {"Header 1","Header 2", "Header 3"} ;
    enum TableFieldType rowTypes[] = {STRING, INT, STRING} ;
    Table *testTable = createTable(2, 3, headerArray, rowTypes) ;

    int int_1 = 3 ;
    int int_2 = 5 ;
    void *testStrings[2][3] = {
        {"Ciao a Tutti", &int_1, "Tutto Bene"},
        {"Alla Vita", &int_2, "Di riveder se stessa nella morte"} 
    } ;

    for (int i = 0 ; i < 2 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
            setTableElem(testTable, i, j, testStrings[i][j]) ;
        }
    }
    printTable(testTable) ;
}

void test3() {
    char *headerArray[] = {"Header 1","Header 2", "Header 3"} ;
    enum TableFieldType rowTypes[] = {STRING, DATE, TIME} ;
    Table *testTable = createTable(9, 3, headerArray, rowTypes) ;

    Date date = {2022, 18, 02} ;
    Time time = {12, 5, 0} ;

    void *testStrings[9][3] = {
        {"Ciao a Tutti", &date, &time},
        {"Alla Vita", &date, &time} ,
        {"Ciao a Tutti", &date, &time},
        {"Alla è Vita", &date, &time} ,
        {"Alla Vita", &date, &time} ,
        {"Alla Vita", &date, &time},
        {"Alla Vita", &date, &time} ,
        {"Alla Vita", &date, &time} ,
        {"Alla Vita", &date, &time}
    } ;

    for (int i = 0 ; i < testTable->rowsNum ; i++) {
        for (int j = 0 ; j < testTable->colsNum ; j++) {
            setTableElem(testTable, i, j, testStrings[i][j]) ;
        }
        printf("Row %d\n", i) ;
    }
    
    printTable(testTable) ;

    freeTable(testTable) ;
}



int main() {

    //TODO Trovare un modo per risolvere con caratteri speciali come è, é, ò, à
    test1() ;
    test2() ;
    test3() ;

    return 0 ;
}

