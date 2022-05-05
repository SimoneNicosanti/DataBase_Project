#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../utils/IOUtils.h"

void showMenu(char **menuOptionsArray, int optionsNumber) {
    for (int i = 0 ; i < optionsNumber ; i++) {
        printf("%d. %s\n", i, menuOptionsArray[i]) ;
    }
    printf("Scegliere Opzione [%d-%d] >>> ", 0, optionsNumber - 1) ;
}

void showOptionHeader() {
    int headerSize = 75 ;
    printf("\n") ;
    for (int i = 0 ; i < headerSize ; i ++) putchar('*') ;
    printf("\n") ;
}

void printOptionTitle(char *optionName) {
    colorPrint(optionName, GREEN_TEXT) ;
    printf("\n") ;
}