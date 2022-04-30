#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "../code/config/EnvironmentSetter.h"
#include "../code/db/Connector.h"
#include "TestUtils.h"

void testWithEnvironment() {
    printf("Test Connessione Con Ambiente Configurato\n") ;
    loadConfiguration() ;

    if (connectToDatabase()) {
        printResponse(true) ;
    }
    else {
        printResponse(false) ;
    }
}

void testWithNoEnvironment() {
    printf("Test Connessione Senza Ambiente Configurato\n") ;
    if (!connectToDatabase()) {
        printResponse(true) ;
    }
    else {
        printResponse(false) ;
    }
    
}


int main() {
    testWithNoEnvironment() ;
    testWithEnvironment() ;
}