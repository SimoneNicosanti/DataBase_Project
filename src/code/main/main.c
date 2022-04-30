#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "MainHeader.h"
#include "code/config/EnvironmentSetter.h"



void main() {
    showAppHeader() ;
    if (!loadConfiguration()) {
        exitWithError() ;
    }
    /* if (connectToDatabase() == true) {
        showLoginView() ;
    } */
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

