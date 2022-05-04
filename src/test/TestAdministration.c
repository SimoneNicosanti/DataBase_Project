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

void testAddTeacher() {
    Class testClass ;
    Teacher testTeacher ;

    strcpy(testTeacher.teacherName, "Simone Nicosanti") ;
    strcpy(testClass.levelName, "Elementary") ;
    testClass.classCode = 1 ;

    if (assignTeacherToClass(&testTeacher, &testClass)) printSuccess() ;
    else printFailure() ;
}

void testOrganizeActivity() {
    CuturalActivity testActivity ;
    
    Date testDate ;
    testDate.year = 2022 ;
    testDate.month = 02 ;
    testDate.day = 18 ;

    Time testTime ;
    testTime.hour = 12 ;
    testTime.minute = 30 ;
    testTime.second = 0 ;

    testActivity.activityDate = testDate ;
    testActivity.activityTime = testTime ;
    strcpy(testActivity.filmTitle, "I Segreti di Silente") ;
    strcpy(testActivity.filmDirector, "Non Lo So") ;
    testActivity.type = FILM ;

    if (organizeActivityInDatabase(&testActivity)) printSuccess() ;
    else printFailure() ;
}

int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(AMMINISTRAZIONE) ;
    
    testAddLevel() ;
    testAddClass() ;
    testAddTeacher() ;

    testOrganizeActivity() ;

    return 0 ;
}