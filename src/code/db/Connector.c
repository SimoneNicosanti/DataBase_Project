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
MYSQL_STMT *addTeacherProcedure ;
MYSQL_STMT *assignClassProcedure ;
MYSQL_STMT *organizeActivityProcedure ;

MYSQL_STMT *addStudentProcedure ;



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
            if (!setupPreparedStatement(&addTeacherProcedure, "CALL aggiungi_insegnante(?,?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Insegnante'") ;
                return false ;
            }
            if (!setupPreparedStatement(&assignClassProcedure, "CALL assegna_corso(?,?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Assegna Corso'") ;
                return false ;
            }
            if (!setupPreparedStatement(&organizeActivityProcedure, "CALL organizza_attivita_culturale(?,?,?,?,?,?,?) ;", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Organizza Attività'") ;
                return false ;
            }
            break ;

        case SEGRETERIA :
            if (!setupPreparedStatement(&addStudentProcedure, "CALL aggiungi_allievo(?,?,?,?,?)", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Allievo'") ;
                return false ;
            }
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
    if (addTeacherProcedure) {
        mysql_stmt_close(addTeacherProcedure) ;
        addTeacherProcedure = NULL ;
    }
    if (assignClassProcedure) {
        mysql_stmt_close(assignClassProcedure) ;
        assignClassProcedure = NULL ;
    }
    if (organizeActivityProcedure) {
        mysql_stmt_close(organizeActivityProcedure) ;
        organizeActivityProcedure = NULL ;
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




