#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "MainHeader.h"
#include "../config/EnvironmentSetter.h"
#include "../db/Connector.h"
#include "../controller/LoginControllerHeader.h"
#include "../utils/TimeUtils.h"

int main() {
    showAppHeader() ;
    if (!loadConfiguration()) {
        //exitWithError() ;
    }
    if (connectToDatabase() && compileTimeRegex()) {
        loginController() ;
    } 
}


void showAppHeader() {
    char appTitleHeader[100] ;
    sprintf(appTitleHeader, "| %s |", APP_TITLE) ;

    printHeaderLine(strlen(appTitleHeader)) ;
    printf("\n%s\n", appTitleHeader) ;
    printHeaderLine(strlen(appTitleHeader)) ;
    printf("\n\n") ;
}

void printHeaderLine(int headerLenght) {
    for (int i = 0 ; i < headerLenght ; i++) {
        if (i == 0 || i == headerLenght - 1) putchar('+') ;
        else putchar('-') ;
    }
}

