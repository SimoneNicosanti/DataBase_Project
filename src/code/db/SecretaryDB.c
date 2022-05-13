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


Class **retrieveAllClasses() {

    /* 
        TODO Un altro modo può essere questo:
            - Passo il doppio puntatore come parametro
            - La funzione lo imposta aciò che viene dalla myMalloc
            - Ritorno il numero di entry impostate correttamente
            --> Evito poi a livello di controller di riprendere di nuovo il numero di righe con il ciclo, cosa che può essere lunga per molte entries
    */

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
    Class **classArray = (Class **) myMalloc(sizeof(Class *) * (rowsNumber + 1)) ;
    
    int i = 0 ;
    int hasResult = mysql_stmt_fetch(loadClassesProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {

        Class *class = (Class *) myMalloc(sizeof(Class)) ;
        class->classCode = classCode ;
        strcpy(class->levelName, classLevelName) ;
        class->studentsNumber = classStudentsNumber ;

        class->activationDate.year = mysqlTime.year ;
        class->activationDate.month = mysqlTime.month ;
        class->activationDate.day = mysqlTime.day ;

        classArray[i] = class ;
        hasResult = mysql_stmt_fetch(loadClassesProcedure) ;
        i++ ;
    }

    classArray[rowsNumber] = NULL ;

    freeStatement(loadClassesProcedure, true) ;
    
    return classArray ;
}

CuturalActivity **getAllActivitiesFromDatabase() {
    if (mysql_stmt_execute(loadAllActivitiesProcedure) != 0) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Eseguire Procedura Recupera Attività") ;
        return NULL ;
    }

    mysql_stmt_store_result(loadAllActivitiesProcedure) ;

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

    mysql_stmt_store_result(loadAllActivitiesProcedure) ;
    int  rowsNum = mysql_stmt_num_rows(loadAllActivitiesProcedure) ; //Senza Store non si può usare
    CuturalActivity **activityArray = (CuturalActivity **) myMalloc(sizeof(CuturalActivity *) * (rowsNum + 1)) ;
    
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

        activityArray[i] = activity ;
        hasResult = mysql_stmt_fetch(loadAllActivitiesProcedure) ;
        i++ ;
    }
    
    activityArray[rowsNum] = NULL ;

    freeStatement(loadAllActivitiesProcedure, true) ;

    return activityArray ;
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

bool addAbsenceToDatabase(Absence *newAbsence) {
    MYSQL_BIND param[3] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, newAbsence->studentName, strlen(newAbsence->studentName), false) ;
    
    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(newAbsence->absenceDate), &mysqlDate) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlDate, sizeof(MYSQL_TIME), false) ;

    MYSQL_TIME mysqlTime ;
    prepareTimeParam(&(newAbsence->startTime), &mysqlTime) ;
    bindParam(&param[2], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    if (mysql_stmt_bind_param(addAbsenceProcedure, param) != 0) {
        printStatementError(addAbsenceProcedure, "Bind Parametri Impossibile per 'Aggiungi Assenza'") ;
        freeStatement(addAbsenceProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addAbsenceProcedure) != 0) {
        printStatementError(addAbsenceProcedure, "Esecuzione Impossibile per 'Aggiungi Assenza'") ;
        freeStatement(addAbsenceProcedure, false) ;
        return false ;
    }

    freeStatement(addAbsenceProcedure, true) ;

    return true ;
}


bool bookPrivateLessonInDatabase(PrivateLesson *lesson) {

    MYSQL_BIND param[5] ;
    MYSQL_TIME mysqlTime ;
    MYSQL_TIME mysqlDate ;

    prepareDateParam(&(lesson->lessonDate), &mysqlDate) ;
    bindParam(&param[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;

    prepareTimeParam(&(lesson->startTime), &mysqlTime) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    bindParam(&param[2], MYSQL_TYPE_STRING, lesson->lessonTeacher, strlen(lesson->lessonTeacher), false) ;
    bindParam(&param[3], MYSQL_TYPE_LONG, &(lesson->lessonDurability), sizeof(int), false) ;
    bindParam(&param[4], MYSQL_TYPE_STRING, lesson->lessonStudent, strlen(lesson->lessonTeacher), false) ;

    if (mysql_stmt_bind_param(bookPrivateLessonProcedure, param) != 0) {
        printStatementError(bookPrivateLessonProcedure, "Impossibile Preparare I Parametri Per 'Prenota Lezione'") ;
        freeStatement(bookPrivateLessonProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(bookPrivateLessonProcedure) != 0) {
        printStatementError(bookPrivateLessonProcedure, "Impossibile Eseguire Procedura 'Prenota Lezione'") ;
        freeStatement(bookPrivateLessonProcedure, false) ;
        return false ;
    }

    freeStatement(bookPrivateLessonProcedure, true) ;

    return true ;

    return true ;
}


//TODO IN TUTTE LE BIND MODIFICA IL TIPO PASSATO: Per la Data da MYSQL_TYPE_TIME a MYSQL_TYPE_DATE !!!!