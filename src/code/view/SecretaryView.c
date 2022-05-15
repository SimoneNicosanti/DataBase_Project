#include "SecretaryViewHeader.h"


char *secretaryMenuOption[] = {
    "Aggiungi Allievo",
    "Aggiungi Partecipazione Ad Attività",
    "Prenota Lezione Privata",
    "Aggiungi Assenza" ,
    "Report Assenze Corso",
    "Report Insegnanti Liberi",
    "Report Partecipanti Attività",
    "Quit"
    } ;


int getSecretaryOption() {
    return getUserOption(secretaryMenuOption, 8) ;
}

bool getStudentInfo(Student *studentPtr) {
    printOptionTitle("Inserimento Studente") ;

    if (!getUserInput("Inserire Nome Nuovo Studente >>> ", studentPtr->studentName, STUDENT_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Nome Studente") ;
        return false ;
    }

    if (!getUserInput("Inserire Numero di Telefono >>> ", studentPtr->studentTelephone, STUDENT_TELEPHONE_MAX_LEN + 1)) {
        printError("Errore Lettura Numero di Telefono") ;
        return false ;
    }

    for (int i = 0 ; i < (int) strlen(studentPtr->studentTelephone) ; i++) {
        if (!isdigit(studentPtr->studentTelephone[i])) return false ;
    }

    if (!getDateFromUser(&(studentPtr->studentSubscribeDate), "Inserire Data di Iscrizione [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    if (!getUserInput("Inserire Livello Corso >>> ", (studentPtr->studentClass).levelName, LEVEL_NAME_MAX_LEN + 1)) {
        printError("Errore Inserimeno Nome Livello") ;
        return false ;
    }


    if (!getIntegerFromUser(&(studentPtr->studentClass.classCode), "Inserire Codice Corso >>> ")) {
        printError("Errore Inserimento Codice Corso") ;
        return false ;
    }

    return true ;
}

bool getStudentJoinActivityInfo(char *studentName, int *activityCodePtr) {

    if (!getUserInput("Inserire Nome Allievo >>> ", studentName, STUDENT_NAME_MAX_LEN + 1)) {
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
    if (!getUserInput("Inserire Nome Allievo >>> ", lesson->lessonStudent, STUDENT_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Studente") ;
        return false ;
    }

    if (!getUserInput("Inserire Nome Insegnante >>> ", lesson->lessonTeacher, TEACHER_NAME_MAX_LEN + 1)) {
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


bool getCourseAbsenceReportInfo(char *levelName, int *courseCode) {

    if (!getUserInput("Inserire Nome del Livello >>> ", levelName, LEVEL_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Nome Livello") ;
        return false ;
    }

    if (!getIntegerFromUser(courseCode, "Inserire Codice Corso >>> ")) {
        printError("Errore Lettura Codice Corso") ;
        return false ;
    }

    return true ;
}

bool getAbsenceInfo(Absence *absencePtr) {
    if (!getUserInput("Inserire Nome Allievo >>> ", absencePtr->studentName, STUDENT_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Nome Allievo") ;
        return false ;
    }

    if (!getDateFromUser(&(absencePtr->absenceDate), "Inserire Data Assenza [yyyy-mm-dd] >>> ")) {
        printError("Errore Lettura Data Assenza") ;
        return false ;
    }

    if (!getTimeFromUser(&(absencePtr->startTime), "Inserire Orario Assenza [hh:m] >>> ")) {
        printError("Errore Lettura Orario Assenza") ;
        return false ;
    }

    return true ;
}


bool getFreeTeacherReportInfo(Date *datePtr, Time *timePtr, int *durationPtr) {
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

bool getActivityParticipantsReportInfo(int *activityCode) {
    if (!getIntegerFromUser(activityCode, "Inserire Codice Attività >>> ")) {
        printError("Errore Lettura Codice Attività") ;
        return false ;
    }

    return true ;
}