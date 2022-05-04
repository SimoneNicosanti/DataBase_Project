#pragma once

#include <mysql/mysql.h>
#include <stdbool.h>
#include "../utils/TimeUtils.h"

void bindParam(MYSQL_BIND *mysqlParam, enum enum_field_types mysqlType, void *paramPtr, unsigned long paramSize, bool nullable) ;

void prepareDateParam(Date *datePtr , MYSQL_TIME *mysqlTime) ;

void printMysqlError(MYSQL *conn, char *errorMessage) ;

void printStatementError(MYSQL_STMT *statement, char *errorMessage) ;

void freeStatement(MYSQL_STMT *statement, bool freeResultSet) ;

bool setupPreparedStatement(MYSQL_STMT **statement, char *statementCommand, MYSQL *conn) ;