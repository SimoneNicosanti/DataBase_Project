#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ViewUtilsHeader.h"
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/IOUtils.h"

char *administrationMenuOptions[] = {"Aggiungi Livello", "Quit"} ;

int getAdministrationOption() {
    showMenu(administrationMenuOptions, 2) ;

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