#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "MainHeader.h"



int main() {
    showAppHeader() ;
    /* if (connectToDatabase() == true) {
        showLoginView() ;
    } */
}


void showAppHeader() {
    char appTitleHeader[100] ;
    sprintf(appTitleHeader, "| %s |", appTitle) ;

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