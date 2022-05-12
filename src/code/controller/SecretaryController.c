#include "SecretaryControllerHeader.h"

void printAllClasses() {
    Class **classArray = retrieveAllClasses() ;
    if (classArray == NULL) return ;

    char *headerArray[] = {"Codice", "Livello", "Numero Allievi", "Data Attivazione"} ;
    enum TableFieldType tableField[] = {INT, STRING, INT, DATE} ;
    int num = 0 ;
    while (classArray[num] != NULL) num++ ;
    Table *table = createTable(num, 4, headerArray, tableField) ;

    int i = 0 ;
    while (classArray[i] != NULL) {
        Class *classPtr = classArray[i] ;
        setTableElem(table, i, 0, &(classPtr->classCode)) ;
        setTableElem(table, i, 1, classPtr->levelName) ;
        setTableElem(table, i, 2, &(classPtr->studentsNumber)) ;
        setTableElem(table, i, 3, &(classPtr->activationDate)) ;

        i++ ;
    }
    
    printTable(table) ;
    freeTable(table) ;

    //TODO AGGIUNGERE FREE DEGLI ARRAY RITORNATI
}

void addStudent() {
    printAllClasses() ;
    Student newStudent ;
    if (getStudentInfo(&newStudent)) {
        addStudentToDatabase(&newStudent) ; 
    }
}

void printAllActivities() {
    CuturalActivity **activityArray = getAllActivitiesFromDatabase() ;

    if (activityArray == NULL) return ;

    int num = 0 ;
    while (activityArray[num] != NULL) num++ ;

    char *headerArray[] = {"Codice", "Data", "Orario", "Tipo", "Titolo Film", "Regista", "Conferenziere", "Argomento Conferenza"} ;
    enum TableFieldType typesArray[] = {INT, DATE, TIME, STRING, STRING, STRING, STRING, STRING} ;
    Table *table = createTable(num, 8, headerArray, typesArray) ;

    int i = 0 ;
    while (activityArray[i] != NULL) {
        CuturalActivity *activity = activityArray[i] ;
        setTableElem(table, i, 0, &(activity->activityCode)) ;
        setTableElem(table, i, 1, &(activity->activityDate)) ;
        setTableElem(table, i, 2, &(activity->activityTime)) ;
        setTableElem(table, i, 4, activity->filmTitle) ;
        setTableElem(table, i, 5, activity->filmDirector) ;
        setTableElem(table, i, 6, activity->meetingLecturer) ;
        setTableElem(table, i, 7, activity->meetingArgument) ;

        if (activity->type == FILM) setTableElem(table, i, 3, "F") ;
        else setTableElem(table, i, 3, "C") ;

        i++ ;
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

            case SECRETARY_QUIT :
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