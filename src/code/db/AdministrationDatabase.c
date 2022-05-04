#include "Connector.h"
#include "../utils/IOUtils.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"
#include <string.h>


bool addLevelToDatabase(Level *levelPtr) {

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


bool addClassToDatabase(Class *classPtr) {

    MYSQL_BIND param[2] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, classPtr->levelName, strlen(classPtr->levelName), false) ;

    MYSQL_TIME mysqlDate ;
    prepareDateParam(&(classPtr->activationDate), &mysqlDate) ;

    bindParam(&param[1], MYSQL_TYPE_DATE, &mysqlDate, sizeof(MYSQL_TIME), false) ;

    if (mysql_stmt_bind_param(addClassProcedure, param) != 0) {
        printStatementError(addClassProcedure, "Impossibile Fare Parametri Procedura 'Aggiungi Corso'") ;
        freeStatement(addClassProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addClassProcedure) != 0) {
        printStatementError(addClassProcedure, "Impossibile Eseguire Procedura 'Aggiungi Corso'") ;
        freeStatement(addClassProcedure, false) ;
        return false ;
    }

    classPtr->classCode = mysql_stmt_insert_id(addClassProcedure) ;
    /* if (classPtr->classCode == 0) {
        printStatementError(addClassProcedure, "Impossibile Recuperare ID Corso Aggiunto") ;
        freeStatement(addClassProcedure, false) ;
        return false ;
    } */

    //TODO Aggiunta ripresa ID ultimo corso inserito

    freeStatement(addLevelProcedure, false) ;

    return true ;
}