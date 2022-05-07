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


ClassReport *retrieveAllClasses() {
    if (mysql_stmt_execute(retrieveClassesProcedure) != 0) {
        printStatementError(retrieveClassesProcedure, "Esecuzione Impossibile per 'Recupera Corsi'") ;
        freeStatement(retrieveClassesProcedure, false) ;
        return NULL ;
    }

    //VA FATTO STORE RESULT
    mysql_stmt_store_result(retrieveClassesProcedure);

    int rowNum = mysql_stmt_num_rows(retrieveClassesProcedure) ;

    MYSQL_BIND resultSetCursor[4] ;
    ClassReport *classArray = (ClassReport *) malloc(sizeof(ClassReport *) * rowNum) ;
    if (classArray == NULL) exit(-1) ;

    classArray->allClasses = (Class **) malloc(sizeof(Class *) * rowNum) ;
    classArray->classNumber = rowNum ;

    for (int rowIndex = 0 ; rowIndex < rowNum ; rowIndex++) {
        Class *class = (Class *) malloc(sizeof(Class *)) ;
        if (class == NULL) exit(-1) ;

        MYSQL_TIME time ;
        bindParam(&resultSetCursor[0], MYSQL_TYPE_LONG, &(class->classCode), sizeof(int), false) ;
        bindParam(&resultSetCursor[1], MYSQL_TYPE_VAR_STRING, class->levelName, LEVEL_NAME_MAX_LEN + 1, false) ;
        bindParam(&resultSetCursor[2], MYSQL_TYPE_DATE, &time, sizeof(MYSQL_TIME), false) ;
        bindParam(&resultSetCursor[3], MYSQL_TYPE_LONG, &(class->studentsNumber), sizeof(int), false) ;

        if (mysql_stmt_bind_result(retrieveClassesProcedure, resultSetCursor) != 0) {
            printStatementError(retrieveClassesProcedure, "Impossibile Recuperare i Corsi") ;
            freeStatement(retrieveClassesProcedure, true) ;
            return NULL ;
        }
         
        if (mysql_stmt_fetch(retrieveClassesProcedure) != 0) {
            printStatementError(retrieveClassesProcedure, "Errore Recupero Risultato") ;
            freeStatement(retrieveClassesProcedure, true) ;
            return NULL ;
        }
         
        (classArray->allClasses)[rowIndex] = class ;
    }

    freeStatement(retrieveClassesProcedure, true) ;
     
    return classArray ;
}


bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) {

    MYSQL_BIND param[2] ;
    bindParam(&param[0], MYSQL_TYPE_LONG, activityCode, sizeof(int), false) ;
    bindParam(&param[1], MYSQL_TYPE_STRING, studentName, strlen(studentName), false) ;

    if (mysql_stmt_bind_param(addJoinProcedure, param) != 0) {
        printStatementError(addJoinProcedure, "Bind Parametri Impossibile per 'Aggiungi Partecipazione'") ;
        freeStatement(addJoinProcedure, false) ;
        return false ;
    }

    if (mysql_stmt_execute(addJoinProcedure) != 0) {
        printStatementError(addJoinProcedure, "Esecuzione Impossibile per 'Aggiungi Partecipazione'") ;
        freeStatement(addJoinProcedure, false) ;
        return false ;
    }

    freeStatement(addJoinProcedure, false) ;

    return true ;
}