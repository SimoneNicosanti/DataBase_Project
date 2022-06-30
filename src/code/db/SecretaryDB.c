#include "SecretaryDBHeader.h"

bool addStudentToDatabase(Student *studentPtr) {
    MYSQL_STMT *addStudentProcedure ;
    if (!setupPreparedStatement(&addStudentProcedure, "CALL aggiungi_allievo(?,?,?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Allievo'") ;
        return false ;
    }

    MYSQL_BIND param[4] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, studentPtr->studentName, strlen(studentPtr->studentName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, studentPtr->studentTelephone, strlen(studentPtr->studentTelephone), false) ;

    MYSQL_TIME mysqlSubscribeDate ;
    prepareDateParam(&(studentPtr->studentSubscribeDate), &mysqlSubscribeDate) ;
    bindParam(&param[2], MYSQL_TYPE_DATE, &mysqlSubscribeDate, sizeof(MYSQL_TIME), false) ;

    bindParam(&param[3], MYSQL_TYPE_LONG, &(studentPtr->studentClass.classCode), sizeof(int), false) ;

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

DatabaseResult *getAllActivitiesFromDatabase() {

    MYSQL_STMT *loadAllActivitiesProcedure ;
    if (!setupPreparedStatement(&loadAllActivitiesProcedure, "CALL recupera_attivita()", conn)) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Preparare Procedura 'Recupera Attività'") ;
        return NULL ;
    }

    if (mysql_stmt_execute(loadAllActivitiesProcedure) != 0) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Eseguire Procedura Recupera Attività") ;
        return NULL ;
    }

    mysql_stmt_store_result(loadAllActivitiesProcedure) ;

    int activityCode ;
    char activityFilmTitle[FILM_TITLE_MAX_LEN] ;
    char activityFilmDirector[FILM_DIRECTOR_NAME_MAX_LEN] ;
    char activityMeetingLecturer[MEETING_LECTURER_NAME_MAX_LEN] ;
    char activityMeetingArgument[MEETING_ARGUMENT_MAX_LEN] ;

    int activityType ;

    MYSQL_TIME mysqlDate ;
    MYSQL_TIME mysqlTime ;
    MYSQL_BIND resultParam[8] ;
    bindParam(&resultParam[0], MYSQL_TYPE_LONG, &activityCode, sizeof(int), false) ;
    bindParam(&resultParam[1], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&resultParam[2], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&resultParam[3], MYSQL_TYPE_LONG, &activityType, sizeof(int), false) ;
    bindParam(&resultParam[4], MYSQL_TYPE_STRING, activityFilmTitle, FILM_TITLE_MAX_LEN, true) ;
    bindParam(&resultParam[5], MYSQL_TYPE_STRING, activityFilmDirector, FILM_DIRECTOR_NAME_MAX_LEN, true) ;
    bindParam(&resultParam[6], MYSQL_TYPE_STRING, activityMeetingLecturer, MEETING_LECTURER_NAME_MAX_LEN, true) ;
    bindParam(&resultParam[7], MYSQL_TYPE_STRING, activityMeetingArgument, MEETING_ARGUMENT_MAX_LEN, true) ;

    if (mysql_stmt_bind_result(loadAllActivitiesProcedure, resultParam) != 0) {
        printStatementError(loadAllActivitiesProcedure, "Impossibile Bind Risultato di Recupera Attività") ;
        freeStatement(loadAllActivitiesProcedure, true) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(loadAllActivitiesProcedure) ; //Senza Store non si può usare
    result->rowsSet = myMalloc(sizeof(CuturalActivity *) * result->numRows) ;
    
    int i = 0 ;
    int hasResult = mysql_stmt_fetch(loadAllActivitiesProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        CuturalActivity *activity = (CuturalActivity *) myMalloc(sizeof(CuturalActivity)) ;
        activity->activityCode = activityCode ;
        getDateParam(&(activity->activityDate), &mysqlDate) ;
        getTimeParam(&(activity->activityTime), &mysqlTime) ;

        //TODO Capire un attimo come fare il recupero di valori nulli
        if (activityType == 0) {
            activity->type = FILM ;
            strcpy(activity->filmTitle, activityFilmTitle) ;
            strcpy(activity->filmDirector, activityFilmDirector) ;
            strcpy(activity->meetingLecturer, "") ;
            strcpy(activity->meetingArgument, "") ;
        }
        else {
            activity->type = MEETING ;
            strcpy(activity->filmTitle, "") ;
            strcpy(activity->filmDirector, "") ;
            strcpy(activity->meetingLecturer, activityMeetingLecturer) ;
            strcpy(activity->meetingArgument, activityMeetingArgument) ;
        }

        result->rowsSet[i] = activity ;
        hasResult = mysql_stmt_fetch(loadAllActivitiesProcedure) ;
        i++ ;
    }

    freeStatement(loadAllActivitiesProcedure, true) ;

    return result ;
}


bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) {
    MYSQL_STMT *addJoinProcedure ;
    if (!setupPreparedStatement(&addJoinProcedure, "CALL aggiungi_partecipazione(?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Partecipazione'") ;
        return false ;
    }

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
    MYSQL_STMT *addAbsenceProcedure ;
    if (!setupPreparedStatement(&addAbsenceProcedure, "CALL aggiungi_assenza(?,?,?)", conn)) {
        printStatementError(addAbsenceProcedure, "Impossibile Preparare Procedura 'Aggiungi Assenza'") ;
        return false ;
    }

    MYSQL_BIND param[3] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, newAbsence->studentName, strlen(newAbsence->studentName), false) ;
    
    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(newAbsence->absenceDate), &mysqlDate) ;
    bindParam(&param[1], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;

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
    
    MYSQL_STMT *bookPrivateLessonProcedure ;
    if (!setupPreparedStatement(&bookPrivateLessonProcedure, "CALL prenota_lezione_privata(?,?,?,?,?)", conn)) {
        printStatementError(bookPrivateLessonProcedure, "Impossibile Preparare Procedura 'Prenota Lezione Privata'") ;
        return false ;
    }

    MYSQL_BIND param[5] ;
    MYSQL_TIME mysqlTime ;
    MYSQL_TIME mysqlDate ;

    prepareDateParam(&(lesson->lessonDate), &mysqlDate) ;
    bindParam(&param[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;

    prepareTimeParam(&(lesson->startTime), &mysqlTime) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    bindParam(&param[2], MYSQL_TYPE_STRING, lesson->lessonTeacher, strlen(lesson->lessonTeacher), false) ;
    bindParam(&param[3], MYSQL_TYPE_LONG, &(lesson->lessonDurability), sizeof(int), false) ;
    bindParam(&param[4], MYSQL_TYPE_STRING, lesson->lessonStudent, strlen(lesson->lessonStudent), false) ;

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
}


DatabaseResult *getCourseAbsenceReportDB(int courseCode) {
    MYSQL_STMT *courseAbsenceReportProcedure ;
    if (!setupPreparedStatement(&courseAbsenceReportProcedure, "CALL report_assenze_corso(?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Report Assenze Corso'") ;
        return NULL ;
    }

    MYSQL_BIND param[1] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, &courseCode, sizeof(int), false) ;

    if (mysql_stmt_bind_param(courseAbsenceReportProcedure, param) != 0) {
        printStatementError(courseAbsenceReportProcedure, "Impossibile Bind Parametri per 'Report Assenze Corso'") ;
        freeStatement(courseAbsenceReportProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(courseAbsenceReportProcedure) != 0) {
        printStatementError(courseAbsenceReportProcedure, "Impossibile Eseguire 'Report Assenze Corso'") ;
        freeStatement(courseAbsenceReportProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_store_result(courseAbsenceReportProcedure) != 0) {
        printStatementError(courseAbsenceReportProcedure, "Impossibile Salvare Risultato 'Report Assenze Corso'") ;
        freeStatement(courseAbsenceReportProcedure, true) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(courseAbsenceReportProcedure) ;
    result->rowsSet = myMalloc(sizeof(Student) * result->numRows) ;


    char studentName[STUDENT_NAME_MAX_LEN] ;
    int absenceNumber ;

    MYSQL_BIND returnParam[2] ;
    bindParam(&returnParam[0], MYSQL_TYPE_STRING, studentName, STUDENT_NAME_MAX_LEN, false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_LONG, &absenceNumber, sizeof(int), false) ;
    if (mysql_stmt_bind_result(courseAbsenceReportProcedure, returnParam) != 0) {
        printStatementError(courseAbsenceReportProcedure, "Impossibile Recuperare Risultato 'Report Assenze Corso'") ;
        freeStatement(courseAbsenceReportProcedure, true) ;
        return NULL ;
    }

    int hasResult = mysql_stmt_fetch(courseAbsenceReportProcedure) ; 
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        Student *student = myMalloc(sizeof(Student)) ;
        strcpy(student->studentName, studentName) ;
        student->studentAbsenceNumber = absenceNumber ;

        result->rowsSet[i] = student ;
        hasResult = mysql_stmt_fetch(courseAbsenceReportProcedure) ;
        i++ ;
    }

    freeStatement(courseAbsenceReportProcedure, true) ;

    return result ;
}

 
DatabaseResult *loadFreeTeachersFromDB(Date *date, Time *time, int *duration) {
    MYSQL_STMT *loadFreeTeachersProcedure ;
    if (!setupPreparedStatement(&loadFreeTeachersProcedure, "CALL recupera_insegnanti_liberi(?,?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Report Assenze Corso'") ;
        return NULL ;
    }

    MYSQL_TIME mysqlDate ;
    MYSQL_TIME mysqlTime ;

    prepareDateParam(date, &mysqlDate) ;
    prepareTimeParam(time, &mysqlTime) ;

    MYSQL_BIND param[3] ;
    bindParam(&param[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[2], MYSQL_TYPE_LONG, duration, sizeof(int), false) ;

    if (mysql_stmt_bind_param(loadFreeTeachersProcedure, param) != 0) {
        printStatementError(loadFreeTeachersProcedure, "Bind Parametri Impossibile Per 'Recupera Insegnanti Liberi'") ;
        freeStatement(loadFreeTeachersProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(loadFreeTeachersProcedure) != 0) {
        printStatementError(loadFreeTeachersProcedure, "Esecuzione Impossibile Per 'Recupera Insegnanti Liberi'") ;
        freeStatement(loadFreeTeachersProcedure, false) ;
        return NULL ;
    }

    

    mysql_stmt_store_result(loadFreeTeachersProcedure) ;

    DatabaseResult *result = (DatabaseResult *) myMalloc(sizeof(DatabaseResult)) ;

    result->numRows = mysql_stmt_num_rows(loadFreeTeachersProcedure) ;
    result->rowsSet = (void **) myMalloc(sizeof(char *) * result->numRows) ;

    char teacherName[TEACHER_NAME_MAX_LEN] ;

    MYSQL_BIND resultParam[1] ;
    bindParam(&resultParam[0], MYSQL_TYPE_STRING, teacherName, TEACHER_NAME_MAX_LEN, false) ;

    

    if (mysql_stmt_bind_result(loadFreeTeachersProcedure, resultParam) != 0) {
        printStatementError(loadFreeTeachersProcedure, "Bind Risultato Impossibile Per 'Recupera Insegnanti Liberi'") ;
        freeStatement(loadFreeTeachersProcedure, false) ;
        return NULL ;
    }

    int hasResult = mysql_stmt_fetch(loadFreeTeachersProcedure) ; 
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        char *teacher = (char *) myMalloc(sizeof(char) * (TEACHER_NAME_MAX_LEN)) ;
        strcpy(teacher, teacherName) ;

        result->rowsSet[i] = teacher ;
        hasResult = mysql_stmt_fetch(loadFreeTeachersProcedure) ; 
        i++ ;
    }

    freeStatement(loadFreeTeachersProcedure, true) ;

    return result ;
}


/* DatabaseResult *loadActivityParticipantsFromDatabase(int *activityCode) {
    MYSQL_STMT *loadActivityParticipantsProcedure ;
    if (!setupPreparedStatement(&loadActivityParticipantsProcedure, "CALL recupera_partecipanti_attivita(?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Recupera Partecipanti'") ;
        return NULL ;
    }

    MYSQL_BIND param[1] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, activityCode, sizeof(int), false) ;

    if (mysql_stmt_bind_param(loadActivityParticipantsProcedure, param) != 0) {
        printStatementError(loadActivityParticipantsProcedure, "Bind Parametri Impossibile per 'Recupera Partecipanti'") ;
        freeStatement(loadActivityParticipantsProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(loadActivityParticipantsProcedure) != 0) {
        printStatementError(loadActivityParticipantsProcedure, "Esecuzione Impossibile per 'Recupera Partecipanti'") ;
        freeStatement(loadActivityParticipantsProcedure, false) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    
    mysql_stmt_store_result(loadActivityParticipantsProcedure) ;

    result->numRows = mysql_stmt_num_rows(loadActivityParticipantsProcedure) ;
    result->rowsSet = myMalloc(sizeof(Partecipation *) * result->numRows) ;

    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    char studentTelephone[STUDENT_TELEPHONE_MAX_LEN + 1] ;

    MYSQL_BIND returnParam[2] ;
    bindParam(&returnParam[0], MYSQL_TYPE_STRING, studentName, STUDENT_NAME_MAX_LEN + 1, false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_STRING, studentTelephone, STUDENT_TELEPHONE_MAX_LEN + 1, false) ;

    if (mysql_stmt_bind_result(loadActivityParticipantsProcedure, returnParam) != 0) {
        printStatementError(loadActivityParticipantsProcedure, "Bind Risultato Impossibile per 'Recupera Partecipanti'") ;
        freeStatement(loadActivityParticipantsProcedure, true) ;
        return NULL ;
    }

    int i = 0 ;
    int hasResult = mysql_stmt_fetch(loadActivityParticipantsProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        Partecipation *partecipation = (Partecipation *) myMalloc(sizeof(Partecipation)) ;
        strcpy(partecipation->studentName, studentName) ;
        strcpy(partecipation->studentTelephone, studentTelephone) ;

        result->rowsSet[i] = partecipation ;

        hasResult = mysql_stmt_fetch(loadActivityParticipantsProcedure) ; 
        i++ ;
    }

    freeStatement(loadActivityParticipantsProcedure, true) ;

    mysql_stmt_close(loadActivityParticipantsProcedure) ;

    return result ;
}  */



