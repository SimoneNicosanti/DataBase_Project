#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../view/LoginView.h"
#include "LoginControllerHeader.h"
#include "../db/DatabaseLoginHeader.h"
#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"
#include "AdministrationControllerHeader.h"
#include "SecretaryControllerHeader.h"
#include "TeacherControllerHeader.h"


void successLogin(Role loginRole, char *username) ;


void loginController() {
    LoginCredentials loginCredentials ;

    
    do {
        memset(&loginCredentials, 0, sizeof(LoginCredentials)) ;
        Role loginRole = LOGIN ;

        showLoginView(&loginCredentials) ;
        
        if ((int) strlen(loginCredentials.username) == 0 || (int) strlen(loginCredentials.password) == 0) {
            colorPrint("Username e/o Password Vuoti\n\n", RED_TEXT) ;
            loginRole = LOGIN ;
        }
        else {
            loginRole = attemptLogin(&loginCredentials) ;
            if (loginRole == LOGIN) {
                colorPrint("Username e/o Password Non Valida\n\n", RED_TEXT) ;
            }
            else {
                successLogin(loginRole, loginCredentials.username) ;
            }
        }
    } while (true) ;    
}

void successLogin(Role loginRole, char *username) {
    clearScreen() ;
    showAppHeader() ;
    colorPrint("\n\nUsername e Password Validi\n", GREEN_TEXT) ;

    if (switchRole(loginRole) == false) {
        return ;
    }

    switch (loginRole) {
        case AMMINISTRAZIONE :
            colorPrint("Accesso Come Amministrazione\n", GREEN_TEXT) ;
            administrationController() ;
            break ;
        case SEGRETERIA :
            colorPrint("Accesso Come Segreteria\n", GREEN_TEXT) ;
            secretaryController() ;
            break ;
        case INSEGNANTE :
            colorPrint("Accesso Come Insegnante\n", GREEN_TEXT) ;
            teacherController(username) ;
            break ;
        case LOGIN :
            break ;
    }

    switchRole(LOGIN) ;
    clearScreen() ;
    showAppHeader() ;
}