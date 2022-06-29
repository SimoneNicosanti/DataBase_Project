#include "CommonDBHeader.h"

DatabaseResult *selectAllCourses() {
    MYSQL_STMT *loadClassesProcedure ;
    if (!setupPreparedStatement(&loadClassesProcedure, "CALL recupera_corsi()", conn)) {
        printStatementError(loadClassesProcedure, "Impossibile Preparare Procedura 'Recupera Corsi'") ;
        return NULL ;
    }

    if (mysql_stmt_execute(loadClassesProcedure) != 0) {
        printStatementError(loadClassesProcedure, "Impossibile Eseguire 'Recupera Corsi'") ;
        return NULL ;
    }

    mysql_stmt_store_result(loadClassesProcedure) ;
     
    int classCode ;
    char classLevelName[LEVEL_NAME_MAX_LEN] ;
    int classStudentsNumber ;
    MYSQL_TIME mysqlTime ;
    memset(&mysqlTime, 0, sizeof(MYSQL_TIME)) ;

    MYSQL_BIND resultParam[4] ;
    bindParam(&resultParam[0], MYSQL_TYPE_LONG, &classCode, sizeof(int), false) ;
    bindParam(&resultParam[1], MYSQL_TYPE_VAR_STRING, classLevelName, LEVEL_NAME_MAX_LEN, false) ;
    bindParam(&resultParam[3], MYSQL_TYPE_LONG, &classStudentsNumber, sizeof(int), false) ;
    bindParam(&resultParam[2], MYSQL_TYPE_DATE, &mysqlTime, sizeof(MYSQL_TIME), false) ;

    if (mysql_stmt_bind_result(loadClassesProcedure, resultParam) != 0)  {
        printStatementError(loadClassesProcedure, "Impossibile Recuperare Parametri") ;
        return NULL ;
    }
   
    DatabaseResult *result = myMalloc(sizeof(DatabaseResult)) ;
    result->numRows = mysql_stmt_num_rows(loadClassesProcedure) ;
    result->rowsSet = myMalloc(sizeof(Class *) * result->numRows) ;
    
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

        result->rowsSet[i] = class ;
        hasResult = mysql_stmt_fetch(loadClassesProcedure) ;
        i++ ;
    }

    freeStatement(loadClassesProcedure, true) ;
    
    return result ;
}