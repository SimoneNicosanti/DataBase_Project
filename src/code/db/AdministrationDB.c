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

    if (mysql_stmt_store_result(addClassProcedure) != 0) {
        printStatementError(addClassProcedure, "Store Risultato Impossibile per 'Aggiungi Corso'") ;
        freeStatement(addClassProcedure, true) ;
        return NULL ;
    }
    
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

    int *returnCode = myMalloc(sizeof(int)) ;
    *returnCode = newClassCode ;
    return returnCode ;
}


bool addTeacherToDatabase(Teacher *teacherPtr, char *username) {
    MYSQL_STMT *addTeacherProcedure ;
    if (!setupPreparedStatement(&addTeacherProcedure, "CALL aggiungi_insegnante(?,?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Insegnante'") ;
        return false ;
    }

    MYSQL_BIND param[4] ;
    bindParam(&param[0], MYSQL_TYPE_STRING, teacherPtr->teacherName, strlen(teacherPtr->teacherName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, teacherPtr->teacherNationality, strlen(teacherPtr->teacherNationality), false) ;
    bindParam(&param[2], MYSQL_TYPE_STRING, teacherPtr->teacherAddress, strlen(teacherPtr->teacherAddress), false) ;
    bindParam(&param[3], MYSQL_TYPE_STRING, username, strlen(username), false) ;

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

    return true ;
}

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) {
    MYSQL_STMT *assignClassProcedure ;
    if (!setupPreparedStatement(&assignClassProcedure, "CALL assegna_corso(?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Assegna Corso'") ;
        return false ;
    }
    
    MYSQL_BIND param[2] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, &(classPtr->classCode), sizeof(int), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, teacherPtr->teacherName, strlen(teacherPtr->teacherName), false) ;

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

    return true ;
}

int *organizeActivityInDatabase(CuturalActivity *newActivity) {
    MYSQL_STMT *organizeActivityProcedure ;
    if (!setupPreparedStatement(&organizeActivityProcedure, "CALL organizza_attivita_culturale(?,?,?,?,?,?,?,?) ", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Organizza Attività'") ;
        return NULL ;
    }

    MYSQL_BIND param[8] ;

    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(newActivity->activityDate), &mysqlDate) ;
    MYSQL_TIME mysqlTime ;
    prepareTimeParam(&(newActivity->activityTime), &mysqlTime) ;

    bindParam(&param[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    short int activityType ;
    int activityCode = 0 ;
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
    bindParam(&param[2], MYSQL_TYPE_SHORT, &activityType, sizeof(short int), false) ;
    bindParam(&param[7], MYSQL_TYPE_LONG, &activityCode, sizeof(int), false) ;

    if (mysql_stmt_bind_param(organizeActivityProcedure, param) != 0) {
        printStatementError(organizeActivityProcedure, "Impossibile Bind Parametri di Procedura 'Organizza Attività'") ;
        freeStatement(organizeActivityProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(organizeActivityProcedure) != 0) {
        printStatementError(organizeActivityProcedure, "Impossibile Eseguire Procedura 'Organizza Attività'") ;
        freeStatement(organizeActivityProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_store_result(organizeActivityProcedure) != 0) {
        printStatementError(organizeActivityProcedure, "Store Risultato Impossibile per 'Organizza Attività'") ;
        freeStatement(organizeActivityProcedure, true) ;
        return NULL ;
    }
    
    MYSQL_BIND resultParam ;
    bindParam(&resultParam, MYSQL_TYPE_LONG, &activityCode, sizeof(int), false) ;

    if (mysql_stmt_bind_result(organizeActivityProcedure, &resultParam) != 0) {
        printStatementError(organizeActivityProcedure, "Errore Recupero Codice Nuova Attività") ;
        freeStatement(organizeActivityProcedure, true) ;
        return NULL ;
    }

    if (mysql_stmt_fetch(organizeActivityProcedure) != 0) {
        printStatementError(organizeActivityProcedure, "Errore Fetch del Risultato") ;
        freeStatement(organizeActivityProcedure, true) ;
        return NULL ;
    }
    
    freeStatement(organizeActivityProcedure, true) ;

    int *returnCode = (int *)myMalloc(sizeof(int)) ;
    *returnCode = activityCode ;

    return returnCode ;
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
    if (!setupPreparedStatement(&addLessonToClassProcedure, "CALL aggiungi_lezione(?,?,?,?,?)", conn)) {
        printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Lezione Corso'") ;
        return false ;
    }

    MYSQL_BIND param[5] ;
    MYSQL_TIME mysqlTime ;

    char dayOfWeekString[3 + 1] ;
    prepareDayOfWeekParam(newLesson->dayOfWeek, dayOfWeekString) ;
    bindParam(&param[0], MYSQL_TYPE_STRING, dayOfWeekString, strlen(dayOfWeekString), false) ;
    prepareTimeParam(&(newLesson->startTime), &mysqlTime) ;
    bindParam(&param[1], MYSQL_TYPE_TIME, &mysqlTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&param[2], MYSQL_TYPE_LONG, &(newLesson->classCode), sizeof(int), false) ;
    bindParam(&param[3], MYSQL_TYPE_LONG, &(newLesson->lessonDuration), sizeof(int), false) ;
    bindParam(&param[4], MYSQL_TYPE_STRING, newLesson->teacherName, strlen(newLesson->teacherName) , false) ;
    
    
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
        freeStatement(loadAllTachingProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_store_result(loadAllTachingProcedure) != 0) {
        printStatementError(loadAllTachingProcedure, "Store Risultato Impossibile per 'Recupera Docenze'") ;
        freeStatement(loadAllTachingProcedure, true) ;
        return NULL ;
    }

    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char teacherName[TEACHER_NAME_MAX_LEN] ;
    MYSQL_BIND returnParam[3] ;
    bindParam(&returnParam[0], MYSQL_TYPE_LONG, &classCode, sizeof(int), false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_STRING, levelName, LEVEL_NAME_MAX_LEN, false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_STRING, teacherName, TEACHER_NAME_MAX_LEN, false) ;

    if (mysql_stmt_bind_result(loadAllTachingProcedure, returnParam) != 0) {
        printStatementError(loadAllTachingProcedure, "Errore Bind Del Risultato") ;
        freeStatement(loadAllTachingProcedure, false) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(loadAllTachingProcedure) ;
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

    if (hasResult == 1) {
        printStatementError(loadAllTachingProcedure, "Fetch Risultato Impossibile per 'Recupera Docenze'") ;
        freeStatement(loadAllTachingProcedure, true) ;
        freeDatabaseResult(result) ;
        return NULL ;
    }

    freeStatement(loadAllTachingProcedure, true) ;

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
        freeStatement(generateTeacherReportProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_store_result(generateTeacherReportProcedure) != 0) {
        printStatementError(generateTeacherReportProcedure, "Store Risultato Impossibile per 'Genera Report Insegnante'") ;
        freeStatement(generateTeacherReportProcedure, true) ;
        return NULL ;
    }

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

    DatabaseResult *result = (DatabaseResult *) myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(generateTeacherReportProcedure) ;
    result->rowsSet = myMalloc(sizeof(ReportLesson *) * result->numRows) ;

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

    if (hasResult == 1) {
        printStatementError(generateTeacherReportProcedure, "Fetch Impossibile per 'Report Insegnante'") ;
        freeStatement(generateTeacherReportProcedure, true) ;
        freeDatabaseResult(result) ;
        return NULL ;
    }

    freeStatement(generateTeacherReportProcedure, true) ;

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

    return true ;
}


DatabaseResult *selectAllLevels() {
    MYSQL_STMT *preparedStatement ;
    if (!setupPreparedStatement(&preparedStatement, "CALL recupera_livelli()", conn)) {
        printMysqlError(conn, "Errore Inizializzazione Procedura 'Recupera Livelli'") ;
        return NULL ;
    }

    if (mysql_stmt_execute(preparedStatement) != 0) {
        printStatementError(preparedStatement, "Impossibile Eseguire Procedura 'Recupera Livelli'") ;
        freeStatement(preparedStatement, false) ;
        return NULL ;
    }
    

    if (mysql_stmt_store_result(preparedStatement) != 0) {
        printStatementError(preparedStatement, "Store Risultato Impossibile per 'Recupera Livelli'") ;
        freeStatement(preparedStatement, true) ;
        return NULL ;
    }

    MYSQL_BIND returnParam[3] ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char bookName[LEVEL_BOOK_NAME_MAX_LEN] ;
    int hasExam ;

    bindParam(&returnParam[0], MYSQL_TYPE_STRING, levelName, LEVEL_NAME_MAX_LEN, false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_STRING, bookName, LEVEL_BOOK_NAME_MAX_LEN, false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_LONG, &hasExam, sizeof(int), false) ;

    if (mysql_stmt_bind_result(preparedStatement, returnParam) != 0) {
        printStatementError(preparedStatement, "Impossibile Recuperare Risultato 'Recupera Livelli'") ;
        freeStatement(preparedStatement, false) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(preparedStatement) ;
    result->rowsSet = myMalloc(sizeof(Level *) * result->numRows) ;
    

    int hasResult = mysql_stmt_fetch(preparedStatement) ;
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        Level *level = (Level *) myMalloc(sizeof(Level)) ;
        strcpy(level->levelName, levelName) ;
        strcpy(level->levelBookName, bookName) ;
        level->levelHasExam = hasExam ;

        result->rowsSet[i] = level ;

        hasResult = mysql_stmt_fetch(preparedStatement) ;
        i++ ;
    }

    if (hasResult == 1) {
        printStatementError(preparedStatement, "Fetch Risultato Impossibile per 'Recupera Livelli'") ;
        freeStatement(preparedStatement, true) ;
        freeDatabaseResult(result) ;
        return NULL ;
    }
    
    freeStatement(preparedStatement, true) ;

    return result ;
}


DatabaseResult *selectAllTeachers() {
    MYSQL_STMT *preparedStatement ;
    if (!setupPreparedStatement(&preparedStatement, "CALL recupera_insegnanti()", conn)) {
        printMysqlError(conn, "Errore Inizializzazione Procedura 'Recupera Insegnanti'") ;
        return NULL ;
    }

    if (mysql_stmt_execute(preparedStatement) != 0) {
        printStatementError(preparedStatement, "Impossibile Eseguire Procedura 'Recupera Insegnanti'") ;
        freeStatement(preparedStatement, false) ;
        return NULL ;
    }

    if (mysql_stmt_store_result(preparedStatement) != 0) {
        printStatementError(preparedStatement, "Store Result Impossibile per 'Recupera Insegnanti'") ;
        freeStatement(preparedStatement, true) ;
        return NULL ;
    }

    char teacherName[TEACHER_NAME_MAX_LEN] ;
    char teacherAddress[TEACHER_ADDRESS_MAX_LEN] ;
    char teacherNation[TEACHER_NATIONALITY_MAX_LEN] ;
    
    MYSQL_BIND returnParam[3] ;
    bindParam(&returnParam[0], MYSQL_TYPE_STRING, teacherName, TEACHER_NAME_MAX_LEN, false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_STRING, teacherNation, TEACHER_NATIONALITY_MAX_LEN, false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_STRING, teacherAddress, TEACHER_ADDRESS_MAX_LEN, false) ;

    if (mysql_stmt_bind_result(preparedStatement, returnParam) != 0) {
        printStatementError(preparedStatement, "Impossibile Recuperare Risultato 'Recupera Insegnanti'") ;
        freeStatement(preparedStatement, true) ;
        return NULL ;
    }

    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(preparedStatement) ;
    result->rowsSet = myMalloc(sizeof(Teacher *) * result->numRows) ;

    int hasResult = mysql_stmt_fetch(preparedStatement) ;
    int i = 0 ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        Teacher *teacher = myMalloc(sizeof(Teacher)) ;
        strcpy(teacher->teacherName, teacherName) ;
        strcpy(teacher->teacherAddress, teacherAddress) ;
        strcpy(teacher->teacherNationality, teacherNation) ;

        result->rowsSet[i] = teacher ;
        i++ ;

        hasResult = mysql_stmt_fetch(preparedStatement) ;
    }

    if (hasResult == 1) {
        printStatementError(preparedStatement, "Fetch Impossibile per 'Recupera Insegnanti'") ;
        freeStatement(preparedStatement, true) ;
        freeDatabaseResult(result) ;
        return NULL ;
    }

    freeStatement(preparedStatement, true) ;

    return result ;
} 