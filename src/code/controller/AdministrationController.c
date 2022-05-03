#include <stdbool.h>
#include <stdio.h>
#include "../view/AdministrationViewHeader.h"
#include "AdministrationControllerHeader.h"
#include "../db/AdministrationDatabaseHeader.h"

enum AdministrationControllerOptions {
    ADD_LEVEL = 0,
    QUIT,
} ;


void addLevel() {
    Level level ;
    if (getLevelInfo(&level)) {
        addLevelToDatabase(&level) ;
    }
}


void administrationController() {
    
    do {
        int selectedOption = getAdministrationOption() ;

        switch (selectedOption) {
            case ADD_LEVEL :
                printf("Add Level Option\n") ;
                addLevel() ;
                break ;
        
            case QUIT :
                printf("QUIT\n") ;
                goto exit_loop ;
            
            default :
                printf("INVALID OPTION\n\n") ;
                break ;
        }
    } while (true) ;

    exit_loop:
}