#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utils/IOUtils.h"
#include "../utils/TimeUtils.h"

bool is_null = true ;

/*
    Funzione per preparare un paramentro MYSQL_BIND.
    - mysqlParam : Puntatore al MYSQL_BIND da preparare
    - mysqlType : Tipo di dato MYSQL da legare
    - paramPtr : Puntatore al buffer da cui prendere/in cui inserire l'informazione
    - paramSize : Lunghezza del buffer puntato da paramPtr (strlen / sizeof)
    - nullable : Indica se il paramPtr è NULL
*/
void bindParam(MYSQL_BIND *mysqlParam, enum enum_field_types mysqlType, void *paramPtr, unsigned long paramSize, bool nullable) {

    memset(mysqlParam, 0, sizeof(MYSQL_BIND)) ;

    mysqlParam->buffer = paramPtr ;
    mysqlParam->buffer_type = mysqlType ;
    mysqlParam->buffer_length = paramSize ;

    if (nullable) mysqlParam->is_null = &is_null ;
}

//Fa la Conversione da Tipo Date a MYSQL_TIME
void prepareDateParam(Date *datePtr , MYSQL_TIME *mysqlTime) {

    memset(mysqlTime, 0, sizeof(MYSQL_TIME)) ;

    mysqlTime->day = datePtr->day ;
    mysqlTime->month = datePtr->month ;
    mysqlTime->year = datePtr->year ;
}

//Conversione da Time a MYSQL_TIME
void prepareTimeParam(Time *timePtr, MYSQL_TIME *mysqlTime) {

    memset(mysqlTime, 0, sizeof(MYSQL_TIME)) ;

    mysqlTime->hour = timePtr->hour ;
    mysqlTime->minute = timePtr->minute ;
    //mysqlTime->second = timePtr->second ;
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


/*
 Funzione per liberare uno statement dopo l'esecuzione
    - statement : statement da liberare
    - freeSet : Indica se deve essere consumato il result set ritornato dallo statement
 */
void freeStatement(MYSQL_STMT *statement, bool freeSet) {
    if (freeSet) {
        //Finisco di Scorrerre Tabella Corrente
        int status = mysql_stmt_fetch(statement) ;
        
        while (status != 1 && status != MYSQL_NO_DATA) status = mysql_stmt_fetch(statement) ;
        
        //Finisco di scorrere tutte le possibili tabelle restanti
        status = mysql_stmt_next_result(statement) ;
        //printf("Status %d\n", status) ;
        while (status == 0) {
            
            status = mysql_stmt_fetch(statement) ;
            while (status != 1 && status != MYSQL_NO_DATA) status = mysql_stmt_fetch(statement) ;
            status = mysql_stmt_next_result(statement) ;
        }
    }
    mysql_stmt_free_result(statement) ;
    mysql_stmt_reset(statement) ;
}

// Permette di saltare la prossima tabella di un result set ritornato da statement
void skipTable(MYSQL_STMT *statement) {
    int status = mysql_stmt_next_result(statement) ;
    if (status == 0) {
        status = mysql_stmt_fetch(statement) ;
        while (status != 1 && status != MYSQL_NO_DATA) status = mysql_stmt_fetch(statement) ;
    }
}

//Inizializza uno statement MYSQL
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

