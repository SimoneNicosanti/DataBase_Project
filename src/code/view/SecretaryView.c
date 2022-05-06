#include "SecretaryViewHeader.h"


char *secretaryMenuOption[] = {
    "Aggiungi Allievo",
    "Aggiungi Partecipazione Ad Attività",
    "Quit"
    } ;


int getSecretaryOption() {
    return getUserOption(secretaryMenuOption, 3) ;
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

    for (int i = 0 ; i < strlen(studentPtr->studentTelephone) ; i++) {
        if (!isdigit(studentPtr->studentTelephone[i])) return false ;
    }

    if (!getDateFromUser(&(studentPtr->studentSubscribeDate), "Inserire Data di Iscrizione >>> ")) {
        return false ;
    }

    if (!getUserInput("Inserire Livello Corso >>> ", (studentPtr->studentClass).levelName, LEVEL_NAME_MAX_LEN + 1)) {
        printError("Errore Inserimeno Nome Livello") ;
        return false ;
    }


    if (!getClassCodeFromUser(&(studentPtr->studentClass.classCode))) {
        printError("Errore Inserimento Codice Corso") ;
        return false ;
    }

    return true ;
}

bool getStudentJoinActivityInfo(char *studentName, int *activityCodePtr) {
    return false ;
}