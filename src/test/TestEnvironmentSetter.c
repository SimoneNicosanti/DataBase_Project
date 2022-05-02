#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../code/config/EnvironmentSetter.h"
#include "Test.h"

int main() {
    printf("Test Impostazione Ambiente\n") ;
    if (loadConfiguration() == true) {
        printSuccess() ;
    }
    else {
        printFailure() ;
    }
}