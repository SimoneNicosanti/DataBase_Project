

#include "LoginView.h"



void showLoginView(User *loginCredentialsPtr) {

    /*
        ATTENTO!! Per permettere la lettura di esattamente un massimo di x byte, imposta una dimensione +2 da riservare
        per il terminatore di stringa \0
    */
    printf("Inserire Credenziali Di Accesso\n") ;

    getUserInput("Username >>> ", loginCredentialsPtr->username, USERNAME_MAX_SIZE) ;
    getUserInput("Password >>> ", loginCredentialsPtr->password, PASSWORD_MAX_SIZE) ;

}