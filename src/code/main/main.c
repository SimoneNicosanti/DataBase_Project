#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "MainHeader.h"
#include "../config/EnvironmentSetter.h"
#include "../db/Connector.h"
#include "../controller/LoginControllerHeader.h"
#include "../utils/TimeUtils.h"
#include "../utils/SystemUtilsHeader.h"
#include "../view/ViewUtilsHeader.h"

int main() {
    showAppHeader() ;
    if (!loadConfiguration()) {
        exitWithError("Errore Configurazione Ambiente") ;
    }
    if (connectToDatabase() && compileTimeRegex()) {
        loginController() ;
    } 
}


