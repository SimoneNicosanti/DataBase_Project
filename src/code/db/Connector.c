#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "../utils/IOUtils.h"
#include "Connector.h"
#include "../controller/LoginControllerHeader.h"
#include "DatabaseUtilsHeader.h"


MYSQL *conn ;
MYSQL_STMT *loginProcedure ;
MYSQL_STMT *restartYearProcedure ;
MYSQL_STMT *addLevelProcedure ;
MYSQL_STMT *addClassProcedure ;



bool initializePreparedStatement(Role role) {
    //TODO Altre procedure
    switch (role) {
        case LOGIN :
            if (!setupPreparedStatement(&loginProcedure, "CALL login(?,?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Login'") ;
                return false ;
            }
            break ;
    
        case AMMINISTRAZIONE :
            if (!setupPreparedStatement(&restartYearProcedure, "CALL riavvia_anno() ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Riavvio Anno'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addLevelProcedure, "CALL aggiungi_livello(?,?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Precedura 'Aggiungi Livello'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addClassProcedure, "CALL aggiungi_corso(?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Corso'") ;
                return false ;
            }
            break ;

        case SEGRETERIA :
            break ;

        case INSEGNANTE :
            break ;

    }

    return true ;
}


bool closeAllStatement() {
    if (loginProcedure) {
        mysql_stmt_close(loginProcedure) ;
        loginProcedure = NULL ;
    }
    if (restartYearProcedure) {
        mysql_stmt_close(restartYearProcedure) ;
        restartYearProcedure = NULL ;
    }
    if (addLevelProcedure) {
        mysql_stmt_close(addLevelProcedure) ;
        addLevelProcedure = NULL ;
    }
    if (addClassProcedure) {
        mysql_stmt_close(addClassProcedure) ;
        addClassProcedure = NULL ;
    }
    //TODO Altre Procedure

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




