#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LoginView.h"
#include "../utils/IOUtils.h"
#include "../utils/SystemUtilsHeader.h"


void showLoginView(LoginCredentials *loginCredentialsPtr) {

    /*
        ATTENTO!! Per permettere la lettura di esattamente un massimo di x byte, imposta una dimensione +2 da riservare
        per il terminatore di stringa \0
    */
    int usernameBufferSize = USERNAME_MAX_SIZE + 1 ;
    int passwordBufferSize = PASSWORD_MAX_SIZE + 1 ;

    printf("Inserire Credenziali Di Accesso\n") ;

    getUserInput("Username: ", loginCredentialsPtr->username, usernameBufferSize) ;
    getUserInput("Password: ", loginCredentialsPtr->password, passwordBufferSize) ;

}