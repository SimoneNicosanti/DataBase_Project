#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../view/LoginView.h"
#include "LoginControllerHeader.h"
#include "../db/DatabaseLoginHeader.h"
#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"


void loginController() {

    LoginCredentials *loginCredentialsPtr = (LoginCredentials *) malloc(sizeof(LoginCredentials)) ;
    if (loginCredentialsPtr == NULL) {
        exitWithError("Errore Allocazione Memoria") ;
    }

    memset(loginCredentialsPtr, 0, sizeof(LoginCredentials)) ;
    
    bool loginResult = false ;
    do {
        showLoginView(loginCredentialsPtr) ;
        
        if ((int) strlen(loginCredentialsPtr->username) == 0 || (int) strlen(loginCredentialsPtr->password) == 0) {
            printError("Username e/o Password Vuoti") ;
            loginResult = false ;
        }
        else {
            loginResult = attemptLogin(loginCredentialsPtr) ;
        }
    } while (!loginResult) ;


}