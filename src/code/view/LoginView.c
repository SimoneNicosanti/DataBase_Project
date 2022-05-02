#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LoginView.h"
#include "../utils/IOUtils.h"
#include "../utils/SystemUtilsHeader.h"

#define USERNAME_MAX_SIZE 9
#define PASSWORD_MAX_SIZE 9


void showLoginView(LoginCredentials *loginCredentialsPtr) {

    /*
        ATTENTO!! Per permettere la lettura di esattamente un massimo di x byte, imposta una dimensione +2 da riservare
        per il terminatore di stringa \0
    */
    int usernameBufferSize = USERNAME_MAX_SIZE + 1 ;
    int passwordBufferSize = PASSWORD_MAX_SIZE + 1 ;

    printf("Inserire Credenziali Di Accesso\n") ;

    char *usernameBuffer = malloc(sizeof(char) * usernameBufferSize) ;
    char *passwordBuffer = malloc(sizeof(char) * passwordBufferSize) ;

    if (usernameBuffer == NULL || passwordBuffer == NULL) {
        exitWithError("Errore Allocazione Memoria") ;
    }

    getUserInput("Username: ", usernameBuffer, usernameBufferSize) ;
    getUserInput("Password: ", passwordBuffer, passwordBufferSize) ;

    loginCredentialsPtr->username = usernameBuffer ;
    loginCredentialsPtr->password = passwordBuffer ;

}