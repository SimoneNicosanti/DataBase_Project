#include <stdbool.h>
#include <stdio.h>
#include "../view/AdministrationViewHeader.h"
#include "AdministrationControllerHeader.h"
#include "../db/AdministrationDatabaseHeader.h"
#include "../view/ViewUtilsHeader.h"

enum AdministrationControllerOptions {
    ADD_LEVEL = 0,
    ADD_CLASS,
    ADD_TEACHER,
    ASSIGN_CLASS, 
    ORGANIZE_ACTIVITY,
    QUIT,
} ;


void addLevel() {
    Level level ;
    if (getLevelInfo(&level)) {
        addLevelToDatabase(&level) ;
    }
}

void addClass() {
    Class newClass ;
    if (getClassInfo(&newClass)) {
        addClassToDatabase(&newClass) ;
    }
}

void addTeacher() {
    Teacher newTeacher ;
    if (getTeacherInfo(&newTeacher)) {
        addTeacherToDatabase(&newTeacher) ;
    }
}

void assignClass() {
    Teacher teacher ;
    Class class ;
    if (getTeacherAndClassInfo(&teacher, &class)) {
        assignTeacherToClass(&teacher, &class) ;
    }
}

void organizeActivity() {
    CuturalActivity newActivity ;
    if (getActivityInfo(&newActivity)) {
        organizeActivityInDatabase(&newActivity) ;
    }

}


void administrationController() {
    
    do {
        int selectedOption = getAdministrationOption() ;

        showOptionHeader() ;
        switch (selectedOption) {
            case ADD_LEVEL :
                addLevel() ;
                break ;

            case ADD_CLASS :
                addClass() ;
                break ;

            case ADD_TEACHER :
                addTeacher() ;
                break ;

            case ASSIGN_CLASS :
                assignClass() ;
                break ;

            case ORGANIZE_ACTIVITY :
                organizeActivity() ;
                break ;
        
            case QUIT :
                goto exit_loop ;

            default :
                printf("INVALID OPTION\n\n") ;
                break ;
        }
        showOptionHeader() ;
    } while (true) ;

    exit_loop:
    showOptionHeader() ;
}