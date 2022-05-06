#include "Test.h"


int main() {

    //TODO Trovare un modo per risolvere con caratteri speciali come è, é, ò, à
    Table testTable ;
    
    testTable.tableRows = (char ***) malloc(sizeof(char **) * 2) ;

    (testTable.tableRows)[0] = (char **) malloc(sizeof(char *) * 3) ;
    (testTable.tableRows)[1] = (char **) malloc(sizeof(char *) * 3) ;

    testTable.tableRows[0][0] = "Alla vita non  concesso in sorte" ;
    testTable.tableRows[0][1] = "Tutto bene Tu??" ;
    testTable.tableRows[0][2] = "Come Quando Fuori Piove" ;
    testTable.tableRows[1][0] = "non c'e' male dai" ;
    testTable.tableRows[1][1] = "Sono Contento #############" ;
    testTable.tableRows[1][2] = "Il Conte di Montecristo" ;
    
    testTable.colsNum = 3 ;
    testTable.rowsNum = 2 ;
    
    char *testHeader[3] = {"Header 1", "Header 2", "Header 3"} ;

    testTable.headerArray = testHeader ;

    printTable(&testTable) ;

    return 0 ;
}