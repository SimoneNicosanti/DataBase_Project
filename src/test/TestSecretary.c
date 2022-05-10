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
    ClassReport *classArray = retrieveAllClasses() ;

    if (classArray != NULL) printSuccess() ;
    else {
        printFailure() ;
        return ;
    }

    char *headerArray[] = {"Codice Corso", "Nome Livello", "Numero Allievi", "Data Attivazione"} ;
    enum TableFieldType tableField[] = {INT, STRING, INT, DATE} ;
    Table *table = createTable(classArray->classNumber, 4, headerArray, tableField) ;

    for (int i = 0 ; i < classArray->classNumber ; i++) {
        Class *classPtr = classArray->allClasses[i] ;
        setTableElem(table, i, 0, &(classPtr->classCode)) ;
        setTableElem(table, i, 1, classPtr->levelName) ;
        setTableElem(table, i, 2, &(classPtr->studentsNumber)) ;
        setTableElem(table, i, 3, &(classPtr->activationDate)) ;
    }
    
    printTable(table) ;

    freeTable(table) ;
}

void testGetActivities() {
    ActivitiesReport *activitiesReport = getAllActivitiesFromDatabase() ;

    if (activitiesReport == NULL) return ;

    char *headerArray[] = {"Codice", "Data", "Orario", "Tipo", "Titolo Film", "Regista", "Conferenziere", "Argomento Conferenza"} ;
    enum TableFieldType typesArray[] = {INT, DATE, TIME, STRING, STRING, STRING, STRING, STRING} ;
    Table *table = createTable(activitiesReport->number, 8, headerArray, typesArray) ;
    for (int i = 0 ; i < activitiesReport->number ; i++) {
        CuturalActivity *activity = activitiesReport->allActivities[i] ;
        setTableElem(table, i, 0, &(activity->activityCode)) ;
        setTableElem(table, i, 1, &(activity->activityDate)) ;
        setTableElem(table, i, 2, &(activity->activityTime)) ;
        setTableElem(table, i, 4, activity->filmTitle) ;
        setTableElem(table, i, 5, activity->filmDirector) ;
        setTableElem(table, i, 6, activity->meetingLecturer) ;
        setTableElem(table, i, 7, activity->meetingArgument) ;

        if (activity->type == FILM) setTableElem(table, i, 3, "F") ;
        else setTableElem(table, i, 3, "C") ;
    }

    printTable(table) ;
    freeTable(table) ;
}


void testAddAbsence() {
    Absence testAbsence ;
    strcpy(testAbsence.studentName, "Simone Nicosanti") ;
    testAbsence.absenceDate.year = 2022 ;
    testAbsence.absenceDate.month = 5 ;
    testAbsence.absenceDate.day = 9 ;

    testAbsence.startTime.hour = 9 ;
    testAbsence.startTime.minute = 0 ;

    if (addAbsenceToDatabase(&testAbsence)) printSuccess() ;
    else printFailure() ;
}

int main() {

    loadConfiguration() ;
    connectToDatabase() ;

    switchRole(SEGRETERIA) ;

    //testAddStudent() ;

    //testAddJoin() ;

    //testGetClasses() ;

    //testGetClasses() ;

    //testGetActivities() ;

    testAddAbsence() ;
}