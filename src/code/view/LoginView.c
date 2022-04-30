#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LoginView.h"

char *getUserInput(char *requestString, char *inputBuffer, int inputMaxSize) {
    //Function to get userinput from stdinput
    printf("%s", requestString) ;
    if (fgets(inputBuffer, inputMaxSize, stdin) == NULL) {
        printf("Errore Scansione Input\n") ;
        return NULL ;
    }

    /*
        Rimuove \n letto con fgets
        Se lo \n non è presente nella stringa significa che ho letto un input troppo lungo:
        devo quindi flushare lo stdout
    */
    char *parsedInput = strtok(inputBuffer, "\n") ;

    //Free stdin
    if (strlen(inputBuffer) + 1 == inputMaxSize || parsedInput == NULL) {
        while(getchar() != '\n') ;
        printf("Input Inserito Troppo lungo\n") ;
        return NULL ;
    }
}

void showLoginView() {

    int usernameMaxSize = 10 ;
    int passwordMaxSize = 10 ;

    printf("Inserire Credenziali Di Accesso\n") ;

    char *usernameBuffer = malloc(sizeof(char) * usernameMaxSize) ;
    char *passwordBuffer = malloc(sizeof(char) * passwordMaxSize) ;

    if (usernameBuffer == NULL || passwordBuffer == NULL) {
        printf("ERRORE ALLOCAZIONE MEMORIA\n") ;
        return ;
    }

    getUserInput("Username: ", usernameBuffer, usernameMaxSize) ;
    getUserInput("Password: ", passwordBuffer, passwordMaxSize) ;
}

