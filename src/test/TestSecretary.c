#include "Test.h"


int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(SEGRETERIA) ;

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