#pragma once

#include <stdbool.h>
#include <mysql/mysql.h>
#include "../controller/LoginControllerHeader.h"

#define DB_HOST "DB.HOST"
#define DB_PORT "DB.PORT" 
#define DB_NAME "DB.NAME"

#define DB_LOGIN_USER "LOGIN.USER"
#define DB_LOGIN_PASSWD "LOGIN.PASSWD" 

#define DB_AMMINISTRAZIONE_USER "AMMINISTRAZIONE.USER"
#define DB_AMMINISTRAZIONE_PASSWD "AMMINISTRAZIONE.PASSWD"

#define DB_SEGRETERIA_USER "SEGRETERIA.USER"
#define DB_SEGRETERIA_PASSWD "SEGRETERIA.PASSWD"

#define DB_INSEGNANTE_USER "INSEGNANTE.USER"
#define DB_INSEGNANTE_PASSWD "INSEGNANTE.PASSWD"

extern MYSQL *conn ;

extern MYSQL_STMT *loginProcedure ;
extern MYSQL_STMT *restartYearProcedure ;

bool connectToDatabase() ;

bool initializePreparedStatement(Role role) ;

bool closeAllStatement() ;