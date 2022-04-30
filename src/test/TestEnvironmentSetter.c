#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../code/config/EnvironmentSetter.h"
#include "TestUtils.h"

int main() {
    printf("Test Impostazione Ambiente\n") ;
    if (loadConfiguration() == true) {
        printResponse(true) ;
    }
    else {
        printResponse(true) ;
    }
}