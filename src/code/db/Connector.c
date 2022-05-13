#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "../utils/IOUtils.h"
#include "Connector.h"
#include "../controller/LoginControllerHeader.h"
#include "DatabaseUtilsHeader.h"


MYSQL *conn ;

//Procedure di Login
MYSQL_STMT *loginProcedure ;

//Procedure Amministrazione
MYSQL_STMT *restartYearProcedure ;
MYSQL_STMT *addLevelProcedure ;
MYSQL_STMT *addClassProcedure ;
MYSQL_STMT *addTeacherProcedure ;
MYSQL_STMT *assignClassProcedure ;
MYSQL_STMT *organizeActivityProcedure ;
MYSQL_STMT *addLessonToClassProcedure ;
MYSQL_STMT *loadAllTachingProcedure ;
MYSQL_STMT *loadTeacherActivitiesProcedure ;


//Procedure Segreteria
MYSQL_STMT *addStudentProcedure ;
MYSQL_STMT *addJoinProcedure ;
MYSQL_STMT *loadClassesProcedure ;
MYSQL_STMT *loadAllActivitiesProcedure ;
MYSQL_STMT *addAbsenceProcedure ;
MYSQL_STMT *bookPrivateLessonProcedure ;

//Procedure Insegnante
MYSQL_STMT *generateAgendaProcedure ;


//TODO In DB trovare il modo di gestire i tempi in modo che sia 23:00 + 2 ore = 01:00 e NON 25 !!!!


bool initializePreparedStatement(Role role) {
    //TODO Altre procedure
    switch (role) {
        case LOGIN :
            if (!setupPreparedStatement(&loginProcedure, "CALL login(?,?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Login'") ;
                return false ;
            }
            break ;
    
        case AMMINISTRAZIONE :
            if (!setupPreparedStatement(&restartYearProcedure, "CALL riavvia_anno() ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Riavvio Anno'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addLevelProcedure, "CALL aggiungi_livello(?,?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Precedura 'Aggiungi Livello'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addClassProcedure, "CALL aggiungi_corso(?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Corso'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addTeacherProcedure, "CALL aggiungi_insegnante(?,?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Insegnante'") ;
                return false ;
            }
            if (!setupPreparedStatement(&assignClassProcedure, "CALL assegna_corso(?,?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Assegna Corso'") ;
                return false ;
            }
            if (!setupPreparedStatement(&organizeActivityProcedure, "CALL organizza_attivita_culturale(?,?,?,?,?,?,?) ", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Organizza Attività'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addLessonToClassProcedure, "CALL aggiungi_lezione(?,?,?,?,?,?)", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Lezione Corso'") ;
                return false ;
            }
            if (!setupPreparedStatement(&loadAllTachingProcedure, "CALL recupera_docenze()", conn)) {
                printMysqlError(conn, "Impossibie Preparare Procedura 'Recupera Docenze'") ;
                return false ;
            }
            break ;

        case SEGRETERIA :
            if (!setupPreparedStatement(&addStudentProcedure, "CALL aggiungi_allievo(?,?,?,?,?)", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Allievo'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addJoinProcedure, "CALL aggiungi_partecipazione(?,?)", conn)) {
                printMysqlError(conn, "Impossibile Preparare Procedura 'Aggiungi Partecipazione'") ;
                return false ;
            }
            if (!setupPreparedStatement(&loadClassesProcedure, "CALL recupera_corsi()", conn)) {
                printStatementError(loadClassesProcedure, "Impossibile Preparare Procedura 'Recupera Corsi'") ;
                return false ;
            }
            if (!setupPreparedStatement(&loadAllActivitiesProcedure, "CALL recupera_attivita()", conn)) {
                printStatementError(loadAllActivitiesProcedure, "Impossibile Preparare Procedura 'Recupera Attività'") ;
                return false ;
            }
            if (!setupPreparedStatement(&addAbsenceProcedure, "CALL aggiungi_assenza(?,?,?)", conn)) {
                printStatementError(addAbsenceProcedure, "Impossibile Preparare Procedura 'Aggiungi Assenza'") ;
                return false ;
            }
            if (!setupPreparedStatement(&bookPrivateLessonProcedure, "CALL prenota_lezione_privata(?,?,?,?,?)", conn)) {
                printStatementError(bookPrivateLessonProcedure, "Impossibile Preparare Procedura 'Prenota Lezione Privata'") ;
                return false ;
            }
            
            break ;

        case INSEGNANTE :
            if (!setupPreparedStatement(&generateAgendaProcedure, "CALL genera_agenda(?,?)", conn)) {
                printStatementError(generateAgendaProcedure, "Impossibile Preparare Procedura 'Genera Agenda'") ;
                return false ;
            }
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
    //TODO AGGIUNGERE CHIUSURA DI TUTTE LE PROCEDURE

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