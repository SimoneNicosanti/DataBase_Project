#include "Connector.h"
#include "../utils/IOUtils.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"


bool addLevelToDatabase(Level *levelPtr) {

    MYSQL_BIND param[3] ;

    bindParam(&param[0], MYSQL_TYPE_VAR_STRING, levelPtr->levelName, LEVEL_NAME_MAX_LEN + 1, false) ;
    bindParam(&param[1], MYSQL_TYPE_VAR_STRING, levelPtr->levelBookName, LEVEL_BOOK_NAME_MAX_LEN + 1, false) ;
    bindParam(&param[2], MYSQL_TYPE_BOOL, &(levelPtr->levelHasExam), sizeof(bool), false) ;

    if (mysql_stmt_bind_param(addLevelProcedure, param) == 0) {
        printStatementError(addLevelProcedure, "Impossibile Fare Il Bind Dei Parametri per Procedura Aggiunta Livello") ;
        freeStatement(loginProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addLevelProcedure) == 0) {
        printStatementError(addLevelProcedure, "Impossibile Eseguire Procedura Aggiunta Livello") ;
        freeStatement(loginProcedure, true) ;
        return false ;
    }

    freeStatement(loginProcedure, true) ;

    return true ;
}