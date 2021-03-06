#include "SecretaryViewHeader.h"


char *secretaryMenuOption[] = {
    "Aggiungi Allievo",
    "Aggiungi Partecipazione Ad Attività",
    "Prenota Lezione Privata",
    "Aggiungi Assenza",
    "Report Assenze Corso",
    "Report Insegnanti Liberi",
    "Quit"
    } ;


int getSecretaryOption() {
    return getUserOption(secretaryMenuOption, 7) ;
}

bool getStudentInfo(Student *studentPtr) {
    printOptionTitle(secretaryMenuOption[0]) ;

    if (!getUserInput("Inserire Nome Nuovo Studente >>> ", studentPtr->studentName, STUDENT_NAME_MAX_LEN)) {
        printError("Errore Lettura Nome Studente") ;
        return false ;
    }

    if (!getUserInput("Inserire Numero di Telefono >>> ", studentPtr->studentTelephone, STUDENT_TELEPHONE_MAX_LEN)) {
        printError("Errore Lettura Numero di Telefono") ;
        return false ;
    }
    for (int i = 0 ; i < (int) strlen(studentPtr->studentTelephone) ; i++) {
        if (!isdigit(studentPtr->studentTelephone[i])) return false ;
    }
    if ((int) strlen(studentPtr->studentTelephone) != 10) {
        printError("I Numeri di Telefono Hanno 10 Cifre") ;
        return false ;
    }

    if (!getDateFromUser(&(studentPtr->studentSubscribeDate), "Inserire Data di Iscrizione [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    if (!getIntegerFromUser(&(studentPtr->studentClass.classCode), "Inserire Codice Corso >>> ")) {
        printError("Errore Inserimento Codice Corso") ;
        return false ;
    }

    return true ;
}

bool getStudentJoinActivityInfo(char *studentName, int *activityCodePtr) {
    printOptionTitle(secretaryMenuOption[1]) ;

    if (!getUserInput("Inserire Nome Allievo >>> ", studentName, STUDENT_NAME_MAX_LEN)) {
        printError("Errore Presa Nome Allievo") ;
        return false ;
    }

    if (!getIntegerFromUser(activityCodePtr, "Inserire Codice Attività >>> ")) {
        printError("Errore Inserimento Codice Attivita") ;
        return false ;
    }

    return true ;
}


bool getPrivateLessonInfo(PrivateLesson *lesson) {
    printOptionTitle(secretaryMenuOption[2]) ;

    if (!getUserInput("Inserire Nome Allievo >>> ", lesson->lessonStudent, STUDENT_NAME_MAX_LEN)) {
        printError("Errore Lettura Studente") ;
        return false ;
    }

    if (!getUserInput("Inserire Nome Insegnante >>> ", lesson->lessonTeacher, TEACHER_NAME_MAX_LEN)) {
        printError("Errore Lettura Insegnante") ;
        return false ;
    }

    if (!getDateFromUser(&(lesson->lessonDate), "Inserire Data Lezione [yyyy-mm-dd] >>> ")) {
        printError("Errore Lettura Data Lezione") ;
        return false ;
    }

    if (!(getTimeFromUser(&(lesson->startTime), "Inserire Orario Lezione [hh:mm] >>> "))) {
        printError("Errore Lettura Orario Lezione") ;
        return false ;
    }

    if (!getIntegerFromUser(&(lesson->lessonDurability), "Inserire Durata Lezione In Minuti >>> ")) {
        printError("Errore Lettura Durata Lezione") ;
        return false ;
    }

    return true ;
}


bool getCourseAbsenceReportInfo(int *courseCode) {
    printOptionTitle(secretaryMenuOption[4]) ;

    if (!getIntegerFromUser(courseCode, "Inserire Codice Corso >>> ")) {
        printError("Errore Lettura Codice Corso") ;
        return false ;
    }

    return true ;
}

bool getAbsenceInfo(Absence *absencePtr) {
    printOptionTitle(secretaryMenuOption[3]) ;

    if (!getUserInput("Inserire Nome Allievo >>> ", absencePtr->studentName, STUDENT_NAME_MAX_LEN)) {
        printError("Errore Lettura Nome Allievo") ;
        return false ;
    }

    if (!getDateFromUser(&(absencePtr->absenceDate), "Inserire Data Assenza [yyyy-mm-dd] >>> ")) {
        printError("Errore Lettura Data Assenza") ;
        return false ;
    }

    if (!getTimeFromUser(&(absencePtr->startTime), "Inserire Orario Assenza [hh:mm] >>> ")) {
        printError("Errore Lettura Orario Assenza") ;
        return false ;
    }

    return true ;
}


bool getFreeTeacherReportInfo(Date *datePtr, Time *timePtr, int *durationPtr) {
    printOptionTitle(secretaryMenuOption[5]) ;
    if (!getDateFromUser(datePtr, "Inserire Data [yyyy-mm-dd] >>> ")) {
        printError("Errore Lettura Data Lezione") ;
        return false ;
    }
 
    if (!getTimeFromUser(timePtr, "Inserire Orario [hh:mm] >>> ")) {
        printError("Errore Lettura Orario Lezione") ;
        return false ;
    }

    if (!getIntegerFromUser(durationPtr, "Inserire Durata Impegno >>> ")) {
        printError("Errore Lettura Durata") ;
        return false ;
    }

    return true ;
}



void printFreeTeacherReport(char **teacherNameArray, int arrayLen) {
    char *header[] = {"Nome Insegnante"} ;
    enum TableFieldType types[] = {STRING} ;
    Table *table = createTable(arrayLen, 1, header, types) ;
    for (int i = 0 ; i < arrayLen ; i++) {
        setTableElem(table, i, 0, teacherNameArray[i]) ;
    }

    printTable(table) ;
    freeTable(table) ;
}


void printCourseAbsenceReport(Student **studentArray, int arrayLen) {
    char *header[] = {"Nome Allievo", "Numero Assenze"} ;
    enum TableFieldType types[] = {STRING, INT} ;
    Table *table = createTable(arrayLen, 2, header, types) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        Student *student = studentArray[i] ;
        setTableElem(table, i, 0, student->studentName) ;
        setTableElem(table, i, 1, &(student->studentAbsenceNumber)) ;
    }

    printTable(table) ;
    freeTable(table) ;
}

void printAllActivities(CuturalActivity **activityArray, int arrayLen) {
    char *headerArray[] = {"Codice", "Data", "Orario", "Tipo", "Titolo Film", "Regista", "Conferenziere", "Argomento Conferenza"} ;
    enum TableFieldType typesArray[] = {INT, DATE, TIME, STRING, STRING, STRING, STRING, STRING} ;
    Table *table = createTable(arrayLen, 8, headerArray, typesArray) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        CuturalActivity *activity = activityArray[i] ;
        setTableElem(table, i, 0, &(activity->activityCode)) ;
        setTableElem(table, i, 1, &(activity->activityDate)) ;
        setTableElem(table, i, 2, &(activity->activityTime)) ;
        setTableElem(table, i, 4, activity->filmTitle) ;
        setTableElem(table, i, 5, activity->filmDirector) ;
        setTableElem(table, i, 6, activity->meetingLecturer) ;
        setTableElem(table, i, 7, activity->meetingArgument) ;

        if (activity->type == FILM) setTableElem(table, i, 3, "F") ;
        else setTableElem(table, i, 3, "C") ;
    }

    printTable(table) ;
    freeTable(table) ;
}

