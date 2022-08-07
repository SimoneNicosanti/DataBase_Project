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
    User loginCredentials ;

    do {
        memset(&loginCredentials, 0, sizeof(User)) ;
        Role loginRole = LOGIN ;

        if (!showLoginView(&loginCredentials)) {
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

    if (switchRole(loginRole) == false) {
        return ;
    }

    switch (loginRole) {
        case AMMINISTRAZIONE :
            administrationController() ;
            break ;
        case SEGRETERIA :
            secretaryController() ;
            break ;
        case INSEGNANTE :
            teacherController(username) ;
            break ;
        case LOGIN :
            break ;
    }

    switchRole(LOGIN) ;
    
    clearScreen() ;
    showAppHeader() ;
}