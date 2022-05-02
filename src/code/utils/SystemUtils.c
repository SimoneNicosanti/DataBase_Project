#include "IOUtils.h"
#include <stdlib.h>


void exitWithError(char *errorMessage) {
    printError(errorMessage) ;
    exit(-1) ;
}