#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ViewUtilsHeader.h"
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/IOUtils.h"

char *administrationMenuOptions[] = {
    "Aggiungi Livello", 
    "Aggiungi Corso", 
    "Aggiungi Insegnante", 
    "Assegna Corso", 
    "Organizza Attività",
    "Quit"
    } ;


int getAdministrationOption() {
    printf("\n\n") ;
    colorPrint("Cosa Posso Fare Per Te??", GREEN_HIGH) ;
    printf("\n") ;
    showMenu(administrationMenuOptions, sizeof(administrationMenuOptions) / sizeof(char *)) ;

    char choosenOption[2] ;
    getUserInput("", choosenOption, 2) ;

    int selectedOption = strtol(choosenOption, NULL, 10) ;
    if (errno == EINVAL) {
        selectedOption = -1 ;
        errno = 0 ;
    }
    return selectedOption ;
}

bool getLevelInfo(Level *levelPtr) {
    printOptionTitle(administrationMenuOptions[0]) ;
    
    if (!getUserInput("Inserire Nome Livello >>> ", levelPtr->levelName, LEVEL_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Nome Livello") ;
        return false ;
    }
    if (!getUserInput("Inserire Nome Libro >>> ", levelPtr->levelBookName, LEVEL_BOOK_NAME_MAX_LEN + 1)) {
        printError("Errore Lettura Nome Libro") ;
        return false ;
    }

    //TODO Controllo Input NON VUOTO

    char hasExamString[2] ;
    if (!getUserInput("Il Livello Ha Un Esame?? [y-n] >>> ", hasExamString, 2)) {
        printError("Errore Lettura Esame") ;
        return false ;
    }

    if (strcmp(hasExamString, "y") == 0) {
            levelPtr->levelHasExam = true ;
            printf("ESAME\n") ;
        }
    else if (strcmp(hasExamString, "n") == 0) levelPtr->levelHasExam = false ;
    else {
        printError("Opzione Inserita NON Valida") ;
        return false ;
    }

    return true ;
}


bool getClassInfo(Class *classPtr) {
    printOptionTitle(administrationMenuOptions[1]) ;

    if (!(getUserInput("Inserire Livello del Nuovo Corso >>> ", classPtr->levelName, LEVEL_NAME_MAX_LEN + 1))) {
        printError("Errore Inserimento Nome Livello") ;
        return false ;
    }

    if (!getDateFromUser(&(classPtr->activationDate), "Inserire Data Attivazione Nuovo Corso [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    return true ;
}

bool getTeacherInfo(Teacher *teacherPtr) {
    printOptionTitle(administrationMenuOptions[2]) ;

    if (!getUserInput("Inserire Nome Insegnante >>> ", teacherPtr->teacherName, TEACHER_NAME_MAX_LENGHT + 1)) {
        printError("Errore Inserimento Nome Insegnante") ;
        return false ;
    }

    if (!getUserInput("Inserire Nazionalità Insegnante >>> ", teacherPtr->teacherNationality, TEACHER_NATIONALITY_MAX_LENGHT + 1)) {
        printError("Errore Inserimento Nazionalità") ;
        return false ;
    }

    if (!getUserInput("Inserire Indirizzo Insegnante >>> ", teacherPtr->teacherAddress, TEACHER_ADDRESS_MAX_LENGHT + 1)) {
        printError("Errore Inserimento Indirizzo") ;
        return false ;
    }

    return true ;
}

bool getTeacherAndClassInfo(Teacher *teacherPtr, Class *classPtr) {
    printOptionTitle(administrationMenuOptions[3]) ;

    if (!getUserInput("Inserire Nome Insegnante >>> ", teacherPtr->teacherName, TEACHER_NAME_MAX_LENGHT + 1)) {
        printError("Errore Inserimento Nome Insegnante") ;
        return false ;
    }

    if (!getUserInput("Inserire Livello Corso >>> ", classPtr->levelName, LEVEL_NAME_MAX_LEN + 1)) {
        printError("Errore Inserimento Livello Corso") ;
        return false ;
    }

    char classCode[10 + 1] ;
    if (!getUserInput("Inserire Codice Corso >>> ", classCode, 10 + 1)) {
        printError("Errore Inserimento Codice Corso") ;
        return false ;
    }

    classPtr->classCode = (int) strtol(classCode, NULL, 10) ;
    
    //TODO Controllo Overflow / Underflow Codice inserito ?? è Necessario o ci pensa il DB??

    return true ;
}


bool getActivityInfo(CuturalActivity *activityPtr) {
    printOptionTitle(administrationMenuOptions[4]) ;

    char activityTypeString[2] ;
    if (!getUserInput("Inserire Tipo Di Attivita [P-C] >>> ", activityTypeString, 2)) {
        printError("Errore Inserimento Tipo Attività") ;
        return false ;
    }

    if (strcmp(activityTypeString, "P") != 0 && strcmp(activityTypeString, "C") != 0) {
        printError("Tipo di Attività Non Valido") ;
        return false ;
    }

    if (strcmp(activityTypeString, "P") == 0) {
        activityPtr->type = FILM ;

        if (!getUserInput("Inserire Titolo Film >>> ", activityPtr->filmTitle, FILM_TITLE_MAX_SIZE + 1)) {
            printError("Errore Inserimento Titolo Film") ;
            return false ;
        }
        if (!getUserInput("Inserire Regista Film >>> ", activityPtr->filmDirector, FILM_DIRECTOR_NAME_MAX_SIZE + 1)) {
            printError("Errore Inserimento Regista Film") ;
            return false ;
        }
    }
    else {
        activityPtr->type = MEETING ;

        if (!getUserInput("Inserire Nome Conferenziere >>> ", activityPtr->meetingLecturer, MEETING_LECTURER_NAME_MAX_SIZE + 1)) {
            printError("Errore Inserimento Conferenziere") ;
            return false ;
        }
        if (!getUserInput("Inserire Argomento Conferenza >>> ", activityPtr->meetingArgument, MEETING_ARGUMENT_MAX_SIZE + 1)) {
            printError("Errore Inserimento Argomento Conferenza") ;
            return false ;
        }
    }

    if (!getDateFromUser(&(activityPtr->activityDate), "Inserire Data Attività [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    if (!getTimeFromUser(&(activityPtr->activityTime), "Inserire Orario Attività [hh:mm] >>> ")) {
        return false ;
    }

    return true ;

} 