#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "../code/config/EnvironmentSetter.h"
#include "../code/db/Connector.h"
#include "Test.h"



void testWithEnvironment() {
    printf("Test Connessione Con Ambiente Configurato\n") ;
    loadConfiguration() ;

    if (connectToDatabase()) {
        printSuccess() ;
    }
    else {
        printFailure() ;
    }
}

void testWithNoEnvironment() {
    printf("Test Connessione Senza Ambiente Configurato\n") ;
    if (!connectToDatabase()) {
        printSuccess() ;
    }
    else {
        printFailure() ;
    }
    
}


int main() {
    testWithNoEnvironment() ;
    testWithEnvironment() ;
}