#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../view/LoginView.h"
#include "LoginControllerHeader.h"
#include "../db/DatabaseLoginHeader.h"
#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"


void successLogin(Role loginRole) ;


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
            colorPrint("Username e/o Password Vuoti\n\n", RED_TEXT) ;
            loginRole = LOGIN ;
        }
        else {
            loginRole = attemptLogin(loginCredentialsPtr) ;
            if (loginRole == LOGIN) {
                colorPrint("Username e/o Password Non Valida\n\n", RED_TEXT) ;
            }
            else {
                successLogin(loginRole) ;
            }
        }
    } while (true) ;    
}

void successLogin(Role loginRole) {
    colorPrint("\n\nUsername e Password Validi\n", GREEN_TEXT) ;

    switch (loginRole) {
        case AMMINISTRAZIONE :
            colorPrint("Accesso Come Amministrazione\n", GREEN_TEXT) ;    
            break ;
        case SEGRETERIA :
            colorPrint("Accesso Come Segreteria\n", GREEN_TEXT) ;
            break ;
        case INSEGNANTE :
            colorPrint("Accesso Come Insegnante\n", GREEN_TEXT) ;
            break ;
    }

    bool successRoleSwitch = switchRole(loginRole) ;
}