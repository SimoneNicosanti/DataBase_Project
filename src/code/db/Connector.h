#pragma once

#include <stdbool.h>
#include <mysql/mysql.h>
#include "../controller/LoginControllerHeader.h"

extern MYSQL *conn ;

extern MYSQL_STMT *loginProcedure ;

bool connectToDatabase() ;

bool initializePreparedStatement(Role role) ;