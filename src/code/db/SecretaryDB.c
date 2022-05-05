#include "SecretaryDBHeader.h"

bool addStudentToDatabase(Student *studentPtr) {

    MYSQL_BIND param[5] ;

    bindParam(&param[0], MYSQL_TYPE_STRING, studentPtr->studentName, strlen(studentPtr->studentName), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, studentPtr->studentTelephone, strlen(studentPtr->studentTelephone), false) ;

    MYSQL_TIME mysqlSubscribeDate ;
    prepareDateParam(&(studentPtr->studentSubscribeDate), &mysqlSubscribeDate) ;
    bindParam(&param[2], MYSQL_TYPE_DATE, &mysqlSubscribeDate, sizeof(MYSQL_TIME), false) ;

    bindParam(&param[3], MYSQL_TYPE_LONG, &(studentPtr->studentClass.classCode), sizeof(int), false) ;
    bindParam(&param[4], MYSQL_TYPE_STRING, &(studentPtr->studentClass.levelName), strlen(studentPtr->studentClass.levelName), false) ;

    if (mysql_stmt_bind_param(addStudentProcedure, param) != 0) {
        printStatementError(addStudentProcedure, "Bind Parametri Impossibile Per 'Aggiungi Allievo'") ;
        freeStatement(addStudentProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addStudentProcedure) != 0) {
        printStatementError(addStudentProcedure, "Esecuzione Impossibile Per 'Aggiungi Allievo'") ;
        freeStatement(addStudentProcedure, false) ;
        return false ;
    }

    freeStatement(addStudentProcedure, false) ;

    return true ;
}