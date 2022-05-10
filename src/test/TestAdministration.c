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

    testActivity.activityDate.year = 2017 ;
    testActivity.activityDate.month = 02 ;
    testActivity.activityDate.day = 18 ;

    testActivity.activityTime.hour = 25 ;
    testActivity.activityTime.minute = 15 ;
    testActivity.activityTime.second = 0 ;

    strcpy(testActivity.filmTitle, "I Segreti di Silente") ;
    strcpy(testActivity.filmDirector, "Non Lo So") ;
    testActivity.type = FILM ;

    if (organizeActivityInDatabase(&testActivity)) printSuccess() ;
    else printFailure() ;
}

void testAddLessonToClass1() {
    ClassLesson testLesson ;
    testLesson.classCode = 1 ;
    strcpy(testLesson.classLevel, "Elementary") ;
    testLesson.dayOfWeek = MONDAY ;
    testLesson.lessonDuration = 30 ;

    testLesson.startTime.hour = 12 ;
    testLesson.startTime.minute = 35 ;
    testLesson.startTime.second = 0 ;

    strcpy(testLesson.teacherName, "Mary Shelley") ;

    if (addClassLessonToDatabase(&testLesson)) printSuccess() ;
    else printFailure() ;
}


void testAddLessonToClass2() {
    ClassLesson testLesson ;
    testLesson.classCode = 1 ;
    strcpy(testLesson.classLevel, "Elementary") ;
    testLesson.dayOfWeek = THURSDAY ;
    testLesson.lessonDuration = 180 ;

    testLesson.startTime.hour = 23 ;
    testLesson.startTime.minute = 50 ;
    testLesson.startTime.second = 0 ;

    strcpy(testLesson.teacherName, "Mary Shelley") ;

    if (addClassLessonToDatabase(&testLesson)) printSuccess() ;
    else printFailure() ;
}

int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(AMMINISTRAZIONE) ;
    
    /* testAddLevel() ;
    testAddClass() ;
    testAddTeacher() ;

    testOrganizeActivity() ; */

    testAddLessonToClass1() ;

    testAddLessonToClass2() ;

    return 0 ;
}