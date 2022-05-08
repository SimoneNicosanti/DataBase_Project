#include "SecretaryDBHeader.h"

bool addStudentToDatabase(Student *studentPtr) {

    MYSQL_BIND param[5] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, studentPtr->studentName, strlen(studentPtr->studentName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, studentPtr->studentTelephone, strlen(studentPtr->studentTelephone), false) ;

    MYSQL_TIME mysqlSubscribeDate ;
    prepareDateParam(&(studentPtr->studentSubscribeDate), &mysqlSubscribeDate) ;
    bindParam(&param[2], MYSQL_TYPE_DATE, &mysqlSubscribeDate, sizeof(MYSQL_TIME), false) ;

    bindParam(&param[3], MYSQL_TYPE_LONG, &(studentPtr->studentClass.classCode), sizeof(int), false) ;
    bindParam(&param[4], MYSQL_TYPE_STRING, &(studentPtr->studentClass.levelName), strlen(studentPtr->studentClass.levelName), false) ;

    if (mysql_stmt_bind_param(addStudentProcedure, param) != 0) {
        printStatementError(addStudentProcedure, "Bind Parametri Impossibile Per 'Aggiungi Allievo'") ;
        freeStatement(addStudentProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addStudentProcedure) != 0) {
        printStatementError(addStudentProcedure, "Esecuzione Impossibile Per 'Aggiungi Allievo'") ;
        freeStatement(addStudentProcedure, false) ;
        return false ;
    }

    freeStatement(addStudentProcedure, false) ;

    return true ;
}


ClassReport *retrieveAllClasses() {
    if (mysql_stmt_execute(loadClassesProcedure) != 0) {
        printStatementError(loadClassesProcedure, "Impossibile Eseguire 'Recupera Corsi'") ;
        return NULL ;
    }

    mysql_stmt_store_result(loadClassesProcedure) ;
     
    int classCode ;
    char classLevelName[LEVEL_NAME_MAX_LEN + 1] ;
    int classStudentsNumber ;
    MYSQL_TIME mysqlTime ;
    memset(&mysqlTime, 0, sizeof(MYSQL_TIME)) ;

    MYSQL_BIND resultParam[4] ;
    bindParam(&resultParam[0], MYSQL_TYPE_LONG, &classCode, sizeof(int), false) ;
    bindParam(&resultParam[1], MYSQL_TYPE_VAR_STRING, classLevelName, LEVEL_NAME_MAX_LEN + 1, false) ;
    bindParam(&resultParam[2], MYSQL_TYPE_LONG, &classStudentsNumber, sizeof(int), false) ;
    bindParam(&resultParam[3], MYSQL_TYPE_DATE, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    if (mysql_stmt_bind_result(loadClassesProcedure, resultParam) != 0)  {
        printStatementError(loadClassesProcedure, "Impossibile Recuperare Parametri") ;
        return NULL ;
    }
   
    int rowsNumber = mysql_stmt_num_rows(loadClassesProcedure) ;
    ClassReport *classReport = (ClassReport *) malloc(sizeof(classReport)) ;
    classReport->classNumber = rowsNumber ;
    classReport->allClasses = (Class **) malloc(sizeof(Class *) * rowsNumber) ;
    
    int i = 0 ;
    int hasResult = mysql_stmt_fetch(loadClassesProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {

        Class *class = (Class *) malloc(sizeof(Class)) ;
        class->classCode = classCode ;
        strcpy(class->levelName, classLevelName) ;
        class->studentsNumber = classStudentsNumber ;

        class->activationDate.year = mysqlTime.year ;
        class->activationDate.month = mysqlTime.month ;
        class->activationDate.day = mysqlTime.day ;

        classReport->allClasses[i] = class ;
        hasResult = mysql_stmt_fetch(loadClassesProcedure) ;
        i++ ;
    }

    freeStatement(loadClassesProcedure, true) ;
    
    return classReport ;
}

ActivitiesReport *getAllActivitiesFromDatabase() {
    if (mysql_stmt_execute(loadAllActivitiesProcedure) != 0) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Eseguire Procedura Recupera Attività") ;
        return NULL ;
    }

    int activityCode ;
    char activityFilmTitle[FILM_TITLE_MAX_SIZE + 1] ;
    char activityFilmDirector[FILM_DIRECTOR_NAME_MAX_SIZE + 1] ;
    char activityMeetingLecturer[MEETING_LECTURER_NAME_MAX_SIZE + 1] ;
    char activityMeetingArgument[MEETING_ARGUMENT_MAX_SIZE + 1] ;

    char activityType[50] ;

    MYSQL_TIME mysqlDate ;
    MYSQL_TIME mysqlTime ;
    MYSQL_BIND resultParam[8] ;
    bindParam(&resultParam[0], MYSQL_TYPE_LONG, &activityCode, sizeof(int), false) ;
    bindParam(&resultParam[1], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&resultParam[2], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&resultParam[3], MYSQL_TYPE_STRING, activityType, 50, false) ;
    bindParam(&resultParam[4], MYSQL_TYPE_STRING, activityFilmTitle, FILM_TITLE_MAX_SIZE + 1, true) ;
    bindParam(&resultParam[5], MYSQL_TYPE_STRING, activityFilmDirector, FILM_DIRECTOR_NAME_MAX_SIZE + 1, true) ;
    bindParam(&resultParam[6], MYSQL_TYPE_STRING, activityMeetingLecturer, MEETING_LECTURER_NAME_MAX_SIZE + 1, true) ;
    bindParam(&resultParam[7], MYSQL_TYPE_STRING, activityMeetingArgument, MEETING_ARGUMENT_MAX_SIZE + 1, true) ;

    if (mysql_stmt_bind_result(loadAllActivitiesProcedure, resultParam) != 0) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Bind Risultato di Recupera Attività") ;
        freeStatement(loadAllActivitiesProcedure, true) ;
        return NULL ;
    }

    ActivitiesReport *activityReport = (ActivitiesReport *) myMalloc(sizeof(ActivitiesReport)) ;
    //activityReport->number = mysql_stmt_num_rows(loadAllActivitiesProcedure) ; //Senza Store non si può usare
    activityReport->allActivities = (CuturalActivity **) myMalloc(sizeof(CuturalActivity *) * activityReport->number) ;
    
    int i = 0 ;
    int hasResult = mysql_stmt_fetch(loadAllActivitiesProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        CuturalActivity *activity = (CuturalActivity *) myMalloc(sizeof(CuturalActivity)) ;
        activity->activityCode = activityCode ;
        getDateParam(&(activity->activityDate), &mysqlDate) ;
        getTimeParam(&(activity->activityTime), &mysqlTime) ;

        //Capire un attimo come fare il recupero di valori nulli
        //
        if (strcmp(activityType, "Proiezione") == 0) {
            activity->type = FILM ;
            strcpy(activity->filmTitle, activityFilmTitle) ;
            strcpy(activity->filmDirector, activityFilmDirector) ;
            strcpy(activity->meetingLecturer, "*****") ;
            strcpy(activity->meetingArgument, "*****") ;
        }
        else {
            activity->type = MEETING ;
            strcpy(activity->filmTitle, "*****") ;
            strcpy(activity->filmDirector, "*****") ;
            strcpy(activity->meetingLecturer, activityMeetingLecturer) ;
            strcpy(activity->meetingArgument, activityMeetingArgument) ;
        }

        activityReport->allActivities[i] = activity ;
        hasResult = mysql_stmt_fetch(loadAllActivitiesProcedure) ;
        i++ ;
    }
    activityReport->number = i ;

    freeStatement(loadAllActivitiesProcedure, true) ;

    return activityReport ;
}


bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) {

    MYSQL_BIND param[2] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, activityCode, sizeof(int), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, studentName, strlen(studentName), false) ;

    if (mysql_stmt_bind_param(addJoinProcedure, param) != 0) {
        printStatementError(addJoinProcedure, "Bind Parametri Impossibile per 'Aggiungi Partecipazione'") ;
        freeStatement(addJoinProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addJoinProcedure) != 0) {
        printStatementError(addJoinProcedure, "Esecuzione Impossibile per 'Aggiungi Partecipazione'") ;
        freeStatement(addJoinProcedure, false) ;
        return false ;
    }

    freeStatement(addJoinProcedure, false) ;

    return true ;
}