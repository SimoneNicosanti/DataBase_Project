#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "IOUtils.h"
#include "SystemUtilsHeader.h"


void printError(char *errorMessage) {
    colorPrint(errorMessage, RED_TEXT) ;
    printf("\n\n") ;
}


bool getUserInput(char *requestString, char *resultBuffer, int bufferSize) {
    /*
        Function to get userinput from stdinput.
        Takes max buffer size from stdin and put them in resultBuffer
    */

    printf("%s", requestString) ;

    //Alloco un buffer di dimensione pari alla massima dimensione valida per l'input più uno per lo \n
    char *inputBuffer = (char *) malloc(sizeof(char) * (bufferSize + 1)) ;
    if (inputBuffer == NULL) {
        exitWithError("Errore Allocazione Memoria Buffer di Input") ;
        return false ;
    } 
    //Lettura al massimo di inputMaxSize - 1 caratteri incluso, se lo trova, il \n
    if (fgets(inputBuffer, bufferSize + 1, stdin) == NULL) {
        printError("Errore Scansione Input") ;
        return false ;
    }

    //Rimozione eventuale \n letto da fgets
    for (int i = 0 ; i < (int) strlen(inputBuffer) ; i++) if (inputBuffer[i] == '\n') inputBuffer[i] = '\0' ;

    /*
        Se ho una lunghezza di ciò che ho letto pari al massimo leggibile, 
        significa che sul canale di input è rimasto ALMENO lo \n,
        quindi devo rimuovere il resto dell'input per non leggerlo alla lettura successiva.
        Significa inoltre che ho letto almeno un carattere in più della dimensione massima prevista e quindi l'input
        non è valido
    */
    if ((int) strlen(inputBuffer) == bufferSize) {
        while(getchar() != '\n') ;
        printError("Input Inserito Troppo Lungo\n") ;
        free(inputBuffer) ;
        return false ;
    }

    strcpy(resultBuffer, inputBuffer) ;

    free(inputBuffer) ;

    return true ;
}


void colorPrint(char *printText , TextColorEnum colorEnum) {
    int color = 0 ;
    switch (colorEnum) {
        case (RED_TEXT) :
            color = RED_TEXT_MARK ;
            break;
        case (GREEN_TEXT) :
            color = GREEN_TEXT_MARK ;
            break ;
        case (RED_HIGH) :
            color = RED_HIGH_TEXT_MARK ;
            break ;
        case (GREEN_HIGH) :
            color = GREEN_HIGH_TEXT_MARK ;
            break;
    }

    printf("\033[%dm%s\033[m", color, printText) ;
} 


bool getDateFromUser(Date *datePtr, char *requestString) {
    char dateString[strlen("yyyy-mm-dd") + 1] ;
    if (!(getUserInput(requestString, dateString, strlen("yyyy-mm-dd") + 1))) {
        printError("Errore Inserimento Data") ;
        return false ;
    }

    if (!verifyAndParseDate(datePtr, dateString)) {
        printError("Formato della Data Inserita non Valido") ;
        return false ;
    }

    return true ;
}

bool getTimeFromUser(Time *timePtr, char *requestString) {

    
}