#include "Test.h"



void testAddStudent() {
    Student testStudent ;

    strcpy(testStudent.studentName, "Simone Nicosanti") ;
    strcpy(testStudent.studentTelephone, "3314182627") ;

    testStudent.studentSubscribeDate.year = 2022 ;
    testStudent.studentSubscribeDate.month = 02 ;
    testStudent.studentSubscribeDate.day = 18 ;

    testStudent.studentClass.classCode = 1 ;
    strcpy(testStudent.studentClass.levelName, "Elementary") ;

    if (addStudentToDatabase(&testStudent)) printSuccess() ;
    else printFailure() ;
}

void testAddJoin() {
    int activityCode = 3 ;
    if (addStudentJoinActivityToDatabase("Simone Nicosanti", &activityCode)) printSuccess() ;
    else printFailure() ;
}

void testGetClasses() {
    ClassArray *classArray = retrieveAllClasses() ;

    if (classArray != NULL) printSuccess() ;
    else printFailure() ;

    for (int i = 0 ; i < classArray->classNumber ; i++) {
        Class *classPtr = (classArray->allClasses)[i] ;
        printf("%d %s %d\n", classPtr->classCode, classPtr->levelName, classPtr->studentsNumber) ;
    }
}

int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(SEGRETERIA) ;

    //testAddStudent() ;

    //testAddJoin() ;

    testGetClasses() ;

    //testGetClasses() ;
}