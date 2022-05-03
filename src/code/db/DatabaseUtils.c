#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utils/IOUtils.h"

bool is_null = true ;

void bindParam(MYSQL_BIND *mysqlParam, enum enum_field_types mysqlType, void *paramPtr, unsigned long paramSize, bool nullable) {

    memset(mysqlParam, 0, sizeof(MYSQL_BIND)) ;

    mysqlParam->buffer = paramPtr ;
    mysqlParam->buffer_type = mysqlType ;
    mysqlParam->buffer_length = paramSize ;

    if (nullable) mysqlParam->is_null = &is_null ;
}

void printMysqlError(MYSQL *conn, char *errorMessage) {
    char sqlErrorMessage[500] ;
    sprintf(sqlErrorMessage, "%s\nErrore %d : %s", errorMessage, mysql_errno(conn), mysql_error(conn)) ;
    printError(sqlErrorMessage) ;
}

void printStatementError(MYSQL_STMT *statement, char *errorMessage) {
    char statementErrorMessage[500] ;
    sprintf(statementErrorMessage, "%s\nErrore %d : %s", errorMessage, mysql_stmt_errno(statement), mysql_stmt_error(statement)) ;
    printError(statementErrorMessage) ;
}

void freeStatement(MYSQL_STMT *statement, bool freeSet) {

    if (freeSet) {
        //Consuma Tutti I Possibili Result Set Rimanenti
        int status = mysql_stmt_fetch(statement) ;
        do {
            //Tabella generica del Result Set
            while (true) {
                status = mysql_stmt_fetch(statement) ;
                if (status == 1 || status == MYSQL_NO_DATA) break ;
            }
        
            status = mysql_stmt_next_result(statement) ;

        } while (status == 0) ;
    }

    mysql_stmt_free_result(statement) ;
    mysql_stmt_reset(statement) ;
}


bool setupPreparedStatement(MYSQL_STMT **statement, char *statementCommand, MYSQL *conn) {

    *statement = mysql_stmt_init(conn) ;

    if (*statement == NULL) {
        printMysqlError(conn, "Impossibile Inizializzare Statement") ;
        return false ;
    }

    if (mysql_stmt_prepare(*statement, statementCommand, strlen(statementCommand)) != 0) {
        printStatementError(*statement, "Impossibile Associare Comando e Statement") ;
        return false ;
    }

    bool update = true ;
    mysql_stmt_attr_set(*statement, STMT_ATTR_UPDATE_MAX_LENGTH, &update) ;

    return true ;
}

