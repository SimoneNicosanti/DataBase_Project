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

//Procedure di Login
extern MYSQL_STMT *loginProcedure ;

//Procedure Amministrazione
extern MYSQL_STMT *restartYearProcedure ;
extern MYSQL_STMT *addLevelProcedure ;
extern MYSQL_STMT *addClassProcedure ;
extern MYSQL_STMT *addTeacherProcedure ;
extern MYSQL_STMT *assignClassProcedure ;
extern MYSQL_STMT *organizeActivityProcedure ;
extern MYSQL_STMT *addLessonToClassProcedure ;
extern MYSQL_STMT *loadAllTachingProcedure ;
extern MYSQL_STMT *loadTeacherActivitiesProcedure ;



//Procedure Segreteria
extern MYSQL_STMT *addStudentProcedure ;
extern MYSQL_STMT *addJoinProcedure ;
extern MYSQL_STMT *loadClassesProcedure ;
extern MYSQL_STMT *loadAllActivitiesProcedure ;
extern MYSQL_STMT *addAbsenceProcedure ;
extern MYSQL_STMT *bookPrivateLessonProcedure ;
extern MYSQL_STMT *courseAbsenceReportProcedure ;

//Procedure Insegnante
extern MYSQL_STMT *generateAgendaProcedure ;

bool connectToDatabase() ;

bool initializePreparedStatement(Role role) ;

bool closeAllStatement() ;