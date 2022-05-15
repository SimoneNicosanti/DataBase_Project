#include "SecretaryControllerHeader.h"

void printAllClasses() {
    DatabaseResult *result = retrieveAllClasses() ;
    if (result == NULL) return ;

    char *headerArray[] = {"Codice", "Livello", "Numero Allievi", "Data Attivazione"} ;
    enum TableFieldType tableField[] = {INT, STRING, INT, DATE} ;
    
    Table *table = createTable(result->numRows, 4, headerArray, tableField) ;

    int i = 0 ;
    for(int i = 0 ; i < result->numRows ; i++) {
        Class *classPtr = result->rowsSet[i] ;
        setTableElem(table, i, 0, &(classPtr->classCode)) ;
        setTableElem(table, i, 1, classPtr->levelName) ;
        setTableElem(table, i, 2, &(classPtr->studentsNumber)) ;
        setTableElem(table, i, 3, &(classPtr->activationDate)) ;
    }
    
    printTable(table) ;
    freeTable(table) ;

    freeDatabaseResult(result) ;
}

void addStudent() {
    printAllClasses() ;
    Student newStudent ;
    if (getStudentInfo(&newStudent)) {
        addStudentToDatabase(&newStudent) ; 
    }
}

void printAllActivities() {
    DatabaseResult *result = getAllActivitiesFromDatabase() ;

    if (result == NULL) return ;

    char *headerArray[] = {"Codice", "Data", "Orario", "Tipo", "Titolo Film", "Regista", "Conferenziere", "Argomento Conferenza"} ;
    enum TableFieldType typesArray[] = {INT, DATE, TIME, STRING, STRING, STRING, STRING, STRING} ;
    Table *table = createTable(result->numRows, 8, headerArray, typesArray) ;

    for (int i = 0 ; i < result->numRows ; i++) {
        CuturalActivity *activity = result->rowsSet[i] ;
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

    freeDatabaseResult(result) ;
}

void addStudentJoinActivity() {
    printAllActivities() ;
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    int activityCode ;
    if (getStudentJoinActivityInfo(studentName, &activityCode)) {
        addStudentJoinActivityToDatabase(studentName, &activityCode) ;
    }
}


void bookPrivateLesson() {
    PrivateLesson privateLesson ;
    if (getPrivateLessonInfo(&privateLesson)) {
        bookPrivateLessonInDatabase(&privateLesson) ;
    }
}

void courseAbsenceReport() {
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    int courseCode ;

    if (!getCourseAbsenceReportInfo(levelName, &courseCode)) return ;
   
    DatabaseResult *result = getCourseAbsenceReportDB(levelName, courseCode) ;

    if (result == NULL) return ;

    char *header[] = {"Nome Allievo", "Numero Assenze"} ;
    enum TableFieldType types[] = {STRING, INT} ;
    Table *table = createTable(result->numRows, 2, header, types) ;

    for (int i = 0 ; i < result->numRows ; i++) {
        Student *student = (Student *) result->rowsSet[i] ;
        setTableElem(table, i, 0, student->studentName) ;
        setTableElem(table, i, 1, &(student->studentAbsenceNumber)) ;
    }

    printTable(table) ;
    freeTable(table) ;
    
    freeDatabaseResult(result) ;
}

void addAbsence() {
    Absence absence ;
    if (getAbsenceInfo(&absence)) {
        addAbsenceToDatabase(&absence) ;
    }
}

 
void freeTeacherReport() {
    Date date ;
    Time time ;
    int duration ;

    if (!getFreeTeacherReportInfo(&date, &time, &duration)) return ;
    
    DatabaseResult *result = loadFreeTeachersFromDB(&date, &time, &duration) ;
    if (result == NULL) return ;

    char *header[] = {"Nome Insegnante"} ;
    enum TableFieldType types[] = {STRING} ;
    Table *table = createTable(result->numRows, 1, header, types) ;
    for (int i = 0 ; i < result->numRows ; i++) {
        setTableElem(table, i, 0, result->rowsSet[i]) ;
    }

    printTable(table) ;
    freeTable(table) ;

    freeDatabaseResult(result) ;
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

            case BOOK_LESSON :
                bookPrivateLesson() ;
                break ;

            case ADD_ABSENCE :
                addAbsence() ;
                break ;

            case COURSE_ABSENCE_REPORT :
                courseAbsenceReport() ;
                break ;
            
            case FREE_TEACHER_REPORT :
                freeTeacherReport() ;
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