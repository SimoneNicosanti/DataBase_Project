#include "IOUtils.h"
#include <stdlib.h>


void exitWithError(char *errorMessage) {
    printError(errorMessage) ;
    exit(-1) ;
}

void printLogMessage(char *message) {
    #ifdef DEBUG
        printf("%s\n", message) ;
    #endif
}

void *myMalloc(size_t allocSize) {
    void *returnPtr = malloc(allocSize) ;
    if (returnPtr == NULL) {
        exitWithError("IMPOSSIBILE ALLOCARE MEMORIA\n") ;
    }
    memset(returnPtr, 0, allocSize) ;
    return returnPtr ;
}