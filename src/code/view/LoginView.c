

#include "LoginView.h"



bool showLoginView(User *loginCredentialsPtr) {

    /*
        ATTENTO!! Per permettere la lettura di esattamente un massimo di x byte, imposta una dimensione +2 da riservare
        per il terminatore di stringa \0
    */
    printf("Inserire Credenziali Di Accesso\n") ;

    if (!getUserInput("Username >>> ", loginCredentialsPtr->username, USERNAME_MAX_SIZE)) {
        printError("Errore Lettura Username") ;
        return false ;
    }
    if (!getUserInput("Password >>> ", loginCredentialsPtr->password, PASSWORD_MAX_SIZE)) {
        printError("Errore Lettura Password") ;
        return false ;
    }

    return true ;

}