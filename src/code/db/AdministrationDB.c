#include "AdministrationDatabaseHeader.h"


bool addLevelToDatabase(Level *levelPtr) {
    MYSQL_STMT *addLevelProcedure ;
    if (!setupPreparedStatement(&addLevelProcedure, "CALL aggiungi_livello(?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Precedura 'Aggiungi Livello'") ;
        return false ;
    }

    MYSQL_BIND param[3] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, levelPtr->levelName, strlen(levelPtr->levelName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, levelPtr->levelBookName, strlen(levelPtr->levelBookName), false) ;
    bindParam(&param[2], MYSQL_TYPE_SHORT, &(levelPtr->levelHasExam), sizeof(short int), false) ;

    if (mysql_stmt_bind_param(addLevelProcedure, param) != 0) {
        printStatementError(addLevelProcedure, "Impossibile Fare Il Bind Dei Parametri per Procedura Aggiunta Livello") ;
        freeStatement(addLevelProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addLevelProcedure) != 0) {
        printStatementError(addLevelProcedure, "Impossibile Eseguire Procedura Aggiunta Livello") ;
        freeStatement(addLevelProcedure, false) ;
        return false ;
    }

    freeStatement(addLevelProcedure, false) ;

    mysql_stmt_close(addLevelProcedure) ;

    return true ;
}


int *addClassToDatabase(Class *classPtr) {
    MYSQL_STMT *addClassProcedure ;
    if (!setupPreparedStatement(&addClassProcedure, "CALL aggiungi_corso(?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Corso'") ;
        return NULL ;
    }

    MYSQL_BIND param[3] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, classPtr->levelName, strlen(classPtr->levelName), false) ;

    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(classPtr->activationDate), &mysqlDate) ;

    bindParam(&param[1], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;

    int newClassCode = 0 ;
    bindParam(&param[2], MYSQL_TYPE_LONG, &newClassCode, sizeof(int), false) ;

    if (mysql_stmt_bind_param(addClassProcedure, param) != 0) {
        printStatementError(addClassProcedure, "Impossibile Fare Parametri Procedura 'Aggiungi Corso'") ;
        freeStatement(addClassProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(addClassProcedure) != 0) {
        printStatementError(addClassProcedure, "Impossibile Eseguire Procedura 'Aggiungi Corso'") ;
        freeStatement(addClassProcedure, false) ;
        return NULL ;
    }

    mysql_stmt_store_result(addClassProcedure) ;
    
    MYSQL_BIND resultParam ;
    bindParam(&resultParam, MYSQL_TYPE_LONG, &newClassCode, sizeof(int), false) ;

    if (mysql_stmt_bind_result(addClassProcedure, &resultParam) != 0) {
        printStatementError(addClassProcedure, "Errore Recupero Codice Nuovo Corso") ;
        freeStatement(addClassProcedure, true) ;
        return NULL ;
    }

    if (mysql_stmt_fetch(addClassProcedure) != 0) {
        printStatementError(addClassProcedure, "Errore Fetch del Risultato") ;
        freeStatement(addClassProcedure, true) ;
        return NULL ;
    }
    
    freeStatement(addClassProcedure, true) ;

    mysql_stmt_close(addClassProcedure) ;

    int *returnCode = myMalloc(sizeof(int)) ;
    *returnCode = newClassCode ;
    return returnCode ;
}


bool addTeacherToDatabase(Teacher *teacherPtr) {
    MYSQL_STMT *addTeacherProcedure ;
    if (!setupPreparedStatement(&addTeacherProcedure, "CALL aggiungi_insegnante(?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Insegnante'") ;
        return false ;
    }

    MYSQL_BIND param[3] ;
    bindParam(&param[0], MYSQL_TYPE_STRING, teacherPtr->teacherName, strlen(teacherPtr->teacherName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, teacherPtr->teacherNationality, strlen(teacherPtr->teacherNationality), false) ;
    bindParam(&param[2], MYSQL_TYPE_STRING, teacherPtr->teacherAddress, strlen(teacherPtr->teacherAddress), false) ;

    if (mysql_stmt_bind_param(addTeacherProcedure, param) != 0) {
        printStatementError(addTeacherProcedure, "Impossibile Bind Parametri di Procedura 'Aggiungi Insegnante'") ;
        freeStatement(addTeacherProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addTeacherProcedure) != 0) {
        printStatementError(addTeacherProcedure, "Impossibile Eseguire Procedura 'Aggiungi Insegnante'") ;
        freeStatement(addTeacherProcedure, false) ;
        return false ;
    }

    freeStatement(addTeacherProcedure, false) ;

    mysql_stmt_close(addTeacherProcedure) ;

    return true ;
}

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) {
    MYSQL_STMT *assignClassProcedure ;
    if (!setupPreparedStatement(&assignClassProcedure, "CALL assegna_corso(?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Assegna Corso'") ;
        return false ;
    }
    
    MYSQL_BIND param[3] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, &(classPtr->classCode), sizeof(int), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, classPtr->levelName, strlen(classPtr->levelName), false) ;
    bindParam(&param[2], MYSQL_TYPE_STRING, teacherPtr->teacherName, strlen(teacherPtr->teacherName), false) ;

    if (mysql_stmt_bind_param(assignClassProcedure, param) != 0) {
        printStatementError(assignClassProcedure, "Impossibile Bind Parametri di Procedura 'Assegna Corso'") ;
        freeStatement(assignClassProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(assignClassProcedure) != 0) {
        printStatementError(assignClassProcedure, "Impossibile Eseguire Procedura 'Assegna Corso'") ;
        freeStatement(assignClassProcedure, false) ;
        return false ;
    }

    freeStatement(assignClassProcedure, false) ;

    mysql_stmt_close(assignClassProcedure) ;

    return true ;
}

bool organizeActivityInDatabase(CuturalActivity *newActivity) {
    MYSQL_STMT *organizeActivityProcedure ;
    if (!setupPreparedStatement(&organizeActivityProcedure, "CALL organizza_attivita_culturale(?,?,?,?,?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Organizza Attività'") ;
        return false ;
    }

    MYSQL_BIND param[7] ;

    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(newActivity->activityDate), &mysqlDate) ;
    MYSQL_TIME mysqlTime ;
    prepareTimeParam(&(newActivity->activityTime), &mysqlTime) ;

    bindParam(&param[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    int activityType ;
    if (newActivity->type == FILM) {
        activityType = 0 ;
        bindParam(&param[3], MYSQL_TYPE_STRING, newActivity->filmTitle, strlen(newActivity->filmTitle), false) ;
        bindParam(&param[4], MYSQL_TYPE_STRING, newActivity->filmDirector, strlen(newActivity->filmDirector), false) ;

        bindParam(&param[5], MYSQL_TYPE_NULL, NULL, sizeof(NULL), true) ;
        bindParam(&param[6], MYSQL_TYPE_NULL, NULL, sizeof(NULL), true) ;
    }
    else {
        activityType = 1 ;
        bindParam(&param[3], MYSQL_TYPE_NULL, NULL, sizeof(NULL), true) ;
        bindParam(&param[4], MYSQL_TYPE_NULL, NULL, sizeof(NULL), true) ;

        bindParam(&param[5], MYSQL_TYPE_STRING, newActivity->meetingLecturer, strlen(newActivity->meetingLecturer), false) ;
        bindParam(&param[6], MYSQL_TYPE_STRING, newActivity->meetingArgument, strlen(newActivity->meetingArgument), false) ;
    }
    bindParam(&param[2], MYSQL_TYPE_TINY, &activityType, sizeof(int), false) ;

    if (mysql_stmt_bind_param(organizeActivityProcedure, param) != 0) {
        printStatementError(organizeActivityProcedure, "Impossibile Bind Parametri di Procedura 'Organizza Attività'") ;
        freeStatement(organizeActivityProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(organizeActivityProcedure) != 0) {
        printStatementError(organizeActivityProcedure, "Impossibile Eseguire Procedura 'Organizza Attività'") ;
        freeStatement(organizeActivityProcedure, false) ;
        return false ;
    }

    freeStatement(organizeActivityProcedure, false) ;

    mysql_stmt_close(organizeActivityProcedure) ;

    return true ;
}

void prepareDayOfWeekParam(enum DayOfWeek dayOfWeek, char *dayOfWeekString) {
    switch (dayOfWeek)
    {
    case MONDAY :
        strcpy(dayOfWeekString, "Lun") ;
        break;
    case TUESDAY:
        strcpy(dayOfWeekString, "Mar") ;
        break;
    case WEDNESDAY :
        strcpy(dayOfWeekString, "Mer") ;
        break ;
    case THURSDAY :
        strcpy(dayOfWeekString, "Gio") ;
        break ;
    case FRIDAY :
        strcpy(dayOfWeekString, "Ven") ;
        break ;
    case SATURDAY :
        strcpy(dayOfWeekString, "Sab") ;
        break ;
    case SUNDAY :
        strcpy(dayOfWeekString, "Dom") ;
        break ;
    }
}

bool addClassLessonToDatabase(ClassLesson *newLesson) {
    MYSQL_STMT *addLessonToClassProcedure ;
    if (!setupPreparedStatement(&addLessonToClassProcedure, "CALL aggiungi_lezione(?,?,?,?,?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Lezione Corso'") ;
        return false ;
    }

    MYSQL_BIND param[6] ;
    MYSQL_TIME mysqlTime ;

    char dayOfWeekString[3 + 1] ;
    prepareDayOfWeekParam(newLesson->dayOfWeek, dayOfWeekString) ;
    bindParam(&param[0], MYSQL_TYPE_STRING, dayOfWeekString, strlen(dayOfWeekString), false) ;
    prepareTimeParam(&(newLesson->startTime), &mysqlTime) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[2], MYSQL_TYPE_LONG, &(newLesson->classCode), sizeof(int), false) ;
    bindParam(&param[3], MYSQL_TYPE_STRING, newLesson->classLevel, strlen(newLesson->classLevel), false) ;
    bindParam(&param[4], MYSQL_TYPE_LONG, &(newLesson->lessonDuration), sizeof(int), false) ;
    bindParam(&param[5], MYSQL_TYPE_STRING, newLesson->teacherName, strlen(newLesson->teacherName) , false) ;
    
    
    if (mysql_stmt_bind_param(addLessonToClassProcedure, param) != 0) {
        printStatementError(addLessonToClassProcedure, "Bind Parametri Impossibile per 'Aggiungi Lezione Corso'") ;
        freeStatement(addLessonToClassProcedure, false) ;
        return false ;
    }

    
    if (mysql_stmt_execute(addLessonToClassProcedure) != 0) {
        printStatementError(addLessonToClassProcedure, "Esecuzione Impossibile Per 'Aggiungi Lezione Corso'") ;
        freeStatement(addLessonToClassProcedure, false) ;
        return false ;
    }

    freeStatement(addLessonToClassProcedure, true) ;
    
    mysql_stmt_close(addLessonToClassProcedure) ;

    return true ;
}

DatabaseResult *selectAllTeaching() {
    MYSQL_STMT *loadAllTachingProcedure ;
    if (!setupPreparedStatement(&loadAllTachingProcedure, "CALL recupera_docenze()", conn)) {
        printMysqlError(conn, "Impossibie Preparare Procedura 'Recupera Docenze'") ;
        return NULL ;
    }
    
    if (mysql_stmt_execute(loadAllTachingProcedure) != 0) {
        printStatementError(loadAllTachingProcedure, "Errore Esecuzione Recupero Docenze") ;
        return NULL ;
    }

    mysql_stmt_store_result(loadAllTachingProcedure) ;

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(loadAllTachingProcedure) ;

    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    char teacherName[TEACHER_NAME_MAX_LEN + 1] ;
    MYSQL_BIND returnParam[3] ;
    bindParam(&returnParam[0], MYSQL_TYPE_LONG, &classCode, sizeof(int), false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_STRING, levelName, LEVEL_NAME_MAX_LEN , false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_STRING, teacherName, TEACHER_NAME_MAX_LEN, false) ;

    if (mysql_stmt_bind_result(loadAllTachingProcedure, returnParam) != 0) {
        printStatementError(loadAllTachingProcedure, "Errore Bind Del Risultato") ;
        freeStatement(loadAllTachingProcedure, false) ;
        return NULL ;
    }

    result->rowsSet = myMalloc(sizeof(Teaching *) * result->numRows) ;

    int hasResult = mysql_stmt_fetch(loadAllTachingProcedure) ;
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        Teaching *teaching = (Teaching *) myMalloc(sizeof(Teaching)) ;
        teaching->classCode = classCode ;
        strcpy(teaching->levelName, levelName) ;
        strcpy(teaching->teacherName, teacherName) ;

        result->rowsSet[i] = teaching ;
        hasResult = mysql_stmt_fetch(loadAllTachingProcedure) ;
        i++ ;
    }

    freeStatement(loadAllTachingProcedure, true) ;
    
    mysql_stmt_close(loadAllTachingProcedure) ;

    return result ;
}


DatabaseResult *generateTeacherReportFromDB(char *teacherName, int *yearPtr, int *monthIndexPtr) {
    MYSQL_STMT *generateTeacherReportProcedure ;
    if (!setupPreparedStatement(&generateTeacherReportProcedure, "CALL genera_report_insegnante(?,?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Genera Report Insegnante'") ;
        return NULL ;
    }

    MYSQL_BIND param[3] ;
    bindParam(&param[0], MYSQL_TYPE_STRING, teacherName, strlen(teacherName), false) ;
    bindParam(&param[1], MYSQL_TYPE_LONG, monthIndexPtr, sizeof(int), false) ;
    bindParam(&param[2], MYSQL_TYPE_SHORT, yearPtr, sizeof(int), false) ;

    if (mysql_stmt_bind_param(generateTeacherReportProcedure, param) != 0) {
        printStatementError(generateTeacherReportProcedure, "Bind Parametri Impossibile per 'Genera Report Insegnante'") ;
        freeStatement(generateTeacherReportProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(generateTeacherReportProcedure) != 0) {
        printStatementError(generateTeacherReportProcedure, "Esecuzione Impossibiler Per 'Genera Report Insegnate'") ;
        return NULL ;
    }

    mysql_stmt_store_result(generateTeacherReportProcedure) ;

    DatabaseResult *result = (DatabaseResult *) myMalloc(sizeof(DatabaseResult)) ;

    result->numRows = mysql_stmt_num_rows(generateTeacherReportProcedure) ;
    result->rowsSet = myMalloc(sizeof(ReportLesson) * result->numRows) ;

    MYSQL_BIND returnParam[4] ;
    MYSQL_TIME mysqlDate ;
    MYSQL_TIME mysqlTime ;
    int lessonDuration ;
    char lessonType[5] ;

    bindParam(&returnParam[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_LONG, &lessonDuration, sizeof(int), false) ;
    bindParam(&returnParam[3], MYSQL_TYPE_STRING, lessonType, 5, false) ;

    if (mysql_stmt_bind_result(generateTeacherReportProcedure, returnParam) != 0) {
        printStatementError(generateTeacherReportProcedure, "Bind Risultato Impossibile Per 'Genera Report Insegnante'") ;
        freeStatement(generateTeacherReportProcedure, true) ;
        return NULL ;
    }

    int hasResult = mysql_stmt_fetch(generateTeacherReportProcedure) ;
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        ReportLesson *lesson = myMalloc(sizeof(ReportLesson)) ;
        getDateParam(&(lesson->lessonDate), &mysqlDate) ;
        getTimeParam(&(lesson->startTime), &mysqlTime) ;
        lesson->duration = lessonDuration ;
        lesson->lessonType = (strcmp(lessonType, "C") == 0) ? COURSE : PRIVATE ;

        result->rowsSet[i] = lesson ;
        i++ ;
        hasResult = mysql_stmt_fetch(generateTeacherReportProcedure) ;
    }

    freeStatement(generateTeacherReportProcedure, true) ;

    mysql_stmt_close(generateTeacherReportProcedure) ;

    return result ;
}


bool restartYearDB() {
    MYSQL_STMT *restartYearProcedure ;
    if (!setupPreparedStatement(&restartYearProcedure, "CALL riavvia_anno() ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Riavvio Anno'") ;
        return false ;
    }

    if (mysql_stmt_execute(restartYearProcedure) != 0) {
        printStatementError(restartYearProcedure, "Impossile Eseguire Procedura 'Riavvio Anno'") ;
        return false ;
    }

    freeStatement(restartYearProcedure, false) ;

    mysql_stmt_close(restartYearProcedure) ;

    return true ;
}