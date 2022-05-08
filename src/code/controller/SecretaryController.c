#include "SecretaryControllerHeader.h"

void printAllClasses() {
    ClassReport *classReport = retrieveAllClasses() ;
    if (classReport == NULL) return ;

    char *headerArray[] = {"Codice", "Livello", "Numero Allievi", "Data Attivazione"} ;
    enum TableFieldType tableField[] = {INT, STRING, INT, DATE} ;
    Table *table = createTable(classReport->classNumber, 4, headerArray, tableField) ;

    for (int i = 0 ; i < classReport->classNumber ; i++) {
        Class *classPtr = classReport->allClasses[i] ;
        setTableElem(table, i, 0, &(classPtr->classCode)) ;
        setTableElem(table, i, 1, classPtr->levelName) ;
        setTableElem(table, i, 2, &(classPtr->studentsNumber)) ;
        setTableElem(table, i, 3, &(classPtr->activationDate)) ;
    }
    
    printTable(table) ;
    freeTable(table) ;
    
    for (int i = 0 ; i < classReport->classNumber ; i++) free(classReport->allClasses[i]) ;
    free(classReport) ;
}

void addStudent() {
    printAllClasses() ;
    Student newStudent ;
    if (getStudentInfo(&newStudent)) {
        addStudentToDatabase(&newStudent) ; 
    }
}

void printAllActivities() {
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

void addStudentJoinActivity() {
    printAllActivities() ;
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    int activityCode ;
    if (getStudentJoinActivityInfo(studentName, &activityCode)) {
        addStudentJoinActivityToDatabase(studentName, &activityCode) ;
    }
}


void secretaryController() {

    do {
        int selectedOption = getSecretaryOption() ;

        showOptionHeader() ;
        switch (selectedOption) {

            case ADD_STUDENT :
                addStudent() ;
                break; ;

            case ADD_JOIN_ACTIVITY :
                addStudentJoinActivity() ;
                break ;

            case QUIT :
                goto exit_loop ;

            default :
                printf("INVALID OPTION\n\n") ;
                break ;
        }
        showOptionHeader() ;
    } while (true) ;

    exit_loop:
    showOptionHeader() ;
}