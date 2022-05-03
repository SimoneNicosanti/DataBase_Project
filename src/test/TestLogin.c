#include "Test.h"
#include "../code/controller/LoginControllerHeader.h"


void testNotExistentUser(char *username, char *password) {
    colorPrint("Test Utente Non Esistente\n", GREEN_TEXT) ;
    LoginCredentials credentials ;
    
    strcpy(credentials.username , username) ;
    strcpy(credentials.password, password) ;

    if (attemptLogin(&credentials) == LOGIN) printSuccess() ;
    else printFailure() ;
}

void testExistentUser(char *username, char *password) {
    colorPrint("Test Utente Esistente\n", GREEN_TEXT) ;
    LoginCredentials credentials ;
    
    strcpy(credentials.username , username) ;
    strcpy(credentials.password, password) ;

    if (attemptLogin(&credentials) != LOGIN) printSuccess() ;
    else printFailure() ;
}

void testLongInput(char *username, char *password) {
    colorPrint("Test Input Lungo\n", GREEN_TEXT) ;
    LoginCredentials credentials ;
    
    strcpy(credentials.username , username) ;
    strcpy(credentials.password, password) ;

    if (attemptLogin(&credentials) != LOGIN) printSuccess() ;
    else printFailure() ;
}

void testSwitchUser(Role role) {
    colorPrint("Test Cambio Ruolo Utente\n", GREEN_TEXT) ;
    if (switchRole(role)) printSuccess() ;
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

    testExistentUser("simo_nico.99", "password") ;
    testExistentUser("simo", "nico") ;
    //testLongInput("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", "shshs") ;
    testNotExistentUser("ciao", "bello") ;
    
    testSwitchUser(AMMINISTRAZIONE) ;

    return 0 ;
}

