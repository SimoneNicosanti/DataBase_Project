#include "TeacherDBHeader.h"



DatabaseResult *generateAgendaFromDatabase(char *teacherUsername, int weekIndex) {
    MYSQL_STMT *generateAgendaProcedure ;

    if (!setupPreparedStatement(&generateAgendaProcedure, "CALL genera_agenda(?,?)", conn)) {
        printStatementError(generateAgendaProcedure, "Impossibile Preparare Procedura 'Genera Agenda'") ;
        return false ;
    }

    MYSQL_BIND param[2] ;
    bindParam(&param[0], MYSQL_TYPE_STRING, teacherUsername, strlen(teacherUsername), false) ;
    bindParam(&param[1], MYSQL_TYPE_LONG, &weekIndex, sizeof(int), false) ;

    if (mysql_stmt_bind_param(generateAgendaProcedure, param) != 0) {
        printStatementError(generateAgendaProcedure, "Impossibile Bind Parametri Per 'Genera Agenda'") ;
        freeStatement(generateAgendaProcedure, false) ;
        return NULL ;
    }

    if (mysql_stmt_execute(generateAgendaProcedure) != 0) {
        printStatementError(generateAgendaProcedure, "Impossibile Eseguire Procedure Per 'Genera Agenda'") ;
        freeStatement(generateAgendaProcedure, false) ;
        return NULL ;
    }

    mysql_stmt_store_result(generateAgendaProcedure) ;
    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(generateAgendaProcedure) ;

    result->rowsSet = myMalloc(sizeof(GeneralLesson) * result->numRows) ;

    MYSQL_BIND returnParam[7] ;
    char lessonType[5] ;
    int classCode ;
    char classLevel[LEVEL_NAME_MAX_LEN + 1] ;
    char student[STUDENT_NAME_MAX_LEN + 1] ;
    MYSQL_TIME mysqlDate ;
    MYSQL_TIME mysqlStartTime ;
    MYSQL_TIME mysqlEndTime ;

    bindParam(&returnParam[0], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;
    bindParam(&returnParam[1], MYSQL_TYPE_TIME, &mysqlStartTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&returnParam[2], MYSQL_TYPE_TIME, &mysqlEndTime, sizeof(MYSQL_TIME), false) ;
    bindParam(&returnParam[3], MYSQL_TYPE_STRING, lessonType, 5, false) ;
    bindParam(&returnParam[4], MYSQL_TYPE_LONG, &classCode, sizeof(int), true) ;
    bindParam(&returnParam[5], MYSQL_TYPE_STRING, classLevel, LEVEL_NAME_MAX_LEN + 1, true) ;
    bindParam(&returnParam[6], MYSQL_TYPE_STRING, student, STUDENT_NAME_MAX_LEN + 1, true) ;

    if (mysql_stmt_bind_result(generateAgendaProcedure, returnParam) != 0) {
        printStatementError(generateAgendaProcedure, "Impossibile Recuperare il risultato da 'Genera Agenda'") ;
        freeStatement(generateAgendaProcedure, true) ;
        return NULL ;
    }

    int i = 0 ;
    int hasResult = mysql_stmt_fetch(generateAgendaProcedure) ;
    while (hasResult != 1 && hasResult != MYSQL_NO_DATA) {
        GeneralLesson *lesson = (GeneralLesson *) myMalloc(sizeof(GeneralLesson)) ;
        memset(lesson, 0, sizeof(GeneralLesson)) ;

        getDateParam(&(lesson->lessonDate), &mysqlDate) ;
        getTimeParam(&(lesson->startTime), &mysqlStartTime) ;
        getTimeParam(&(lesson->endTime), &mysqlEndTime) ;
        if (strcmp(lessonType, "C") == 0) lesson->lessonType = COURSE ;
        else lesson->lessonType = PRIVATE ;
        lesson->classCode = classCode ;
        strcpy(lesson->levelName, classLevel) ;
        strcpy(lesson->studentName, student) ;

        result->rowsSet[i] = lesson ;
        hasResult = mysql_stmt_fetch(generateAgendaProcedure) ;
        i++ ;
    }

    freeStatement(generateAgendaProcedure, true) ;

    return result ;

}