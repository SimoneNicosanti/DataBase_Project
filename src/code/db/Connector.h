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
extern MYSQL_STMT *addLevelProcedure ;
extern MYSQL_STMT *addClassProcedure ;
extern MYSQL_STMT *addTeacherProcedure ;
extern MYSQL_STMT *addClassProcedure ;
extern MYSQL_STMT *assignClassProcedure ;
extern MYSQL_STMT *organizeActivityProcedure ;

extern MYSQL_STMT *addStudentProcedure ;
extern MYSQL_STMT *addJoinProcedure ;
extern MYSQL_STMT *loadClassesProcedure ;
extern MYSQL_STMT *loadAllActivitiesProcedure ;
extern MYSQL_STMT *addLessonToClassProcedure ;
extern MYSQL_STMT *loadAllTachingProcedure ;
extern MYSQL_STMT *addAbsenceProcedure ;

bool connectToDatabase() ;

bool initializePreparedStatement(Role role) ;

bool closeAllStatement() ;