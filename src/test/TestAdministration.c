#include "Test.h"


void testAddLevel() {
    Level newLevel ;
    strcpy(newLevel.levelName, "LIVELLO PROVA") ;
    strcpy(newLevel.levelBookName, "get insight 1") ;
    newLevel.levelHasExam = false ;

    if (addLevelToDatabase(&newLevel)) {
        printSuccess() ;
    }
    else {
        printFailure() ;
    }
}

void testAddClass() {
    Class testClass ;

    strcpy(testClass.levelName, "LIVELLO PROVA") ;

    testClass.activationDate.year = 2022 ;
    testClass.activationDate.month = 05 ;
    testClass.activationDate.day = 23 ;

    int insertedClassID = addClassToDatabase(&testClass) ;
    if (insertedClassID) {
        printSuccess() ;
    }
    else {
        printf("Codice Classe %d\n", testClass.classCode) ;
        printFailure() ;
    }

}

int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(AMMINISTRAZIONE) ;
    
    testAddLevel() ;

    testAddClass() ;

    return 0 ;
}