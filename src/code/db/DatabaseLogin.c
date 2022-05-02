#include "DatabaseLoginHeader.h"
#include <mysql/mysql.h>
#include "../controller/LoginControllerHeader.h"
#include "Connector.h"
#include "DatabaseUtilsHeader.h"
#include <string.h>
#include <stdio.h>

Role attemptLogin(LoginCredentials *loginCredentials) {

    MYSQL_BIND param[3] ;
    int role = LOGIN ; // Default set to LOGIN

    bindParam(&param[0], MYSQL_TYPE_VAR_STRING, loginCredentials->username, strlen(loginCredentials->username)) ; //Set username Param
    bindParam(&param[1], MYSQL_TYPE_VAR_STRING, loginCredentials->password, strlen(loginCredentials->password)) ; // Bind password Param
    bindParam(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role)) ;

    if (mysql_stmt_bind_param(loginProcedure, param) != 0) {
        printStatementError(loginProcedure, "Impossibile Fare Binding Dei Parametri di Login") ;
        freeStatement(loginProcedure) ;
        return role ;
    }

    if (mysql_stmt_execute(loginProcedure) != 0) {
        printStatementError(loginProcedure, "Impossibile Eseguire Procedeura di Login") ;
        freeStatement(loginProcedure) ;
        return role ;
    }

    bindParam(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role)) ;

    if (mysql_stmt_bind_result(loginProcedure, &param[2]) != 0) {
        printStatementError(loginProcedure, "Impossibile Recuperare Risultato di Login") ;
        freeStatement(loginProcedure) ;
        return role ;
    }

    if (mysql_stmt_fetch(loginProcedure) != 0) {
        printStatementError(loginProcedure, "Impossibile Salvare Risultato di Login") ;
        freeStatement(loginProcedure) ;
        return role ;
    }

    int status = mysql_stmt_fetch(loginProcedure) ;
    while (status > 0 && status != MYSQL_NO_DATA) status = mysql_stmt_fetch(loginProcedure) ;

    freeStatement(loginProcedure) ;

    return role ;

}


void switchRole(Role role) {

}