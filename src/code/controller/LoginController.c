#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../view/LoginView.h"
#include "LoginControllerHeader.h"
#include "../db/DatabaseLoginHeader.h"
#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"


void loginController() {
    //Vedere se allocare dinamicamente o su stack
    LoginCredentials *loginCredentialsPtr = (LoginCredentials *) malloc(sizeof(LoginCredentials)) ;
    if (loginCredentialsPtr == NULL) {
        exitWithError("Errore Allocazione Memoria") ;
    }

    memset(loginCredentialsPtr, 0, sizeof(LoginCredentials)) ;
    
    Role loginRole = LOGIN ;
    do {
        showLoginView(loginCredentialsPtr) ;
        
        if ((int) strlen(loginCredentialsPtr->username) == 0 || (int) strlen(loginCredentialsPtr->password) == 0) {
            printError("Username e/o Password Vuoti") ;
            loginRole = LOGIN ;
        }
        else {
            loginRole = attemptLogin(loginCredentialsPtr) ;
        }
    } while (loginRole == LOGIN) ;

    switch (loginRole) {
        case AMMINISTRAZIONE :
            break ;
        case SEGRETERIA :
            break ;
        case INSEGNANTE :
            break ;
    }
}