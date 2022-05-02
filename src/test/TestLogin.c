#include "Test.h"
#include "../code/controller/LoginControllerHeader.h"


void testNotExistentUser() {
    colorPrint("Test Utente Non Esistente\n", GREEN_TEXT) ;
    LoginCredentials credentials ;
    
    strcpy(credentials.username , "simo_nico.999") ;
    strcpy(credentials.password, "password") ;

    if (attemptLogin(&credentials) == LOGIN) printSuccess() ;
    else printFailure() ;
}

void testExistentUser() {
    colorPrint("Test Utente Esistente\n", GREEN_TEXT) ;
    LoginCredentials credentials ;
    
    strcpy(credentials.username , "simo_nico.99") ;
    strcpy(credentials.password, "password") ;

    if (attemptLogin(&credentials) != LOGIN) printSuccess() ;
    else printFailure() ;
}


int main() {
    if (!loadConfiguration()) {
        printFailure() ;
        return 0;
    }
    if (!connectToDatabase()) {
        printFailure() ;
        return 0;
    }

    testNotExistentUser() ;
    testExistentUser() ;

    return 0 ;
}

