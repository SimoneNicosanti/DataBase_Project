#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ViewUtilsHeader.h"
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/IOUtils.h"

char *administrationMenuOptions[] = {"Aggiungi Livello", "Aggiungi Corso", "Quit"} ;

int getAdministrationOption() {
    showMenu(administrationMenuOptions, sizeof(administrationMenuOptions) / sizeof(char *)) ;

    char choosenOption[2] ;
    getUserInput("", choosenOption, 2) ;

    int selectedOption = strtol(choosenOption, NULL, 10) ;
    return selectedOption ;
}

bool getLevelInfo(Level *levelPtr) {
    printf("\n\n") ;
    
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

    printf("\n") ;

    return true ;
}


bool getClassInfo(Class *classPtr) {
    printf("\n\n") ;

    if (!(getUserInput("Inserire Livello del Nuovo Corso >>> ", classPtr->levelName, LEVEL_NAME_MAX_LEN + 1))) {
        printError("Errore Inserimento Nome Livello") ;
        return false ;
    }

    char dateString[strlen("yyyy-mm-dd") + 1] ;
    if (!(getUserInput("Inserire Data Attivazione Nuovo Corso [yyyy-mm-dd] >>> ", dateString, strlen("yyyy-mm-dd") + 1))) {
        printError("Errore Inserimento Data") ;
        return false ;
    }

    if (!verifyAndParseDate(&(classPtr->activationDate), dateString)) {
        printError("Formato della Data Inserita non Valido") ;
        return false ;
    }

    printf("\n") ;

    return true ;
}