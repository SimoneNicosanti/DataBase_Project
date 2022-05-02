#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "../utils/IOUtils.h"
#include "Connector.h"
#include "../controller/LoginControllerHeader.h"
#include "DatabaseUtilsHeader.h"

const char *DB_HOST = "DB.HOST" ;
const char *DB_PORT = "DB.PORT" ;
const char *DB_NAME = "DB.NAME" ;
const char *DB_LOGIN_USER = "LOGIN.USER" ;
const char *DB_LOGIN_PASSWD = "LOGIN.PASSWD" ;


MYSQL *conn ;
MYSQL_STMT *loginProcedure ;



bool initializePreparedStatement(Role role) {
    
    switch (role) {
        case LOGIN :
            if (!setupPreparedStatement(&loginProcedure, "CALL login(?,?,?) ;", conn)) {
                printError("Impossibile Preparare Procedura di Login") ;
                return false ;
            }
            break ;
    
        case AMMINISTRAZIONE :
            break ;

        case SEGRETERIA :
            break ;

        case INSEGNANTE :
            break ;

    }

    return true ;
}

bool connectToDatabase() {
    char *host = getenv(DB_HOST) ;
    char *port = getenv(DB_PORT) ;
    char *databaseName = getenv(DB_NAME) ;
    char *loginUser = getenv(DB_LOGIN_USER) ;
    char *loginPassword = getenv(DB_LOGIN_PASSWD) ;

    if (host == NULL || port == NULL || loginUser == NULL || loginPassword == NULL || databaseName == NULL) {
        fprintf(stderr, "Variabili d'Ambiente non Trovate\n") ;
        return false ;
    }

    conn = mysql_init(NULL) ;
    if (conn == NULL) {
        fprintf(stderr, "Errore in Inizializzazione Librerie\n") ;
        return false ;
    }

    if (mysql_real_connect(
        conn, 
        host, 
        loginUser, 
        loginPassword, 
        databaseName, 
        atoi(port), 
        NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS | CLIENT_COMPRESS | CLIENT_INTERACTIVE | CLIENT_REMEMBER_OPTIONS) == NULL) {
            fprintf(stderr, "Errore di Connessione al Database\n%s\n\n", mysql_error(conn)) ;
            return false ;
        }    

    return initializePreparedStatement(LOGIN) ;
}




