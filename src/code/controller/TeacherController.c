#include "TeacherControllerHeader.h"


void generateAgenda(char *teacherUsername) {
    int weekIndex ;
    if (getAgendaInfo(&weekIndex)) {
        // Esecuzione DB
    }
}


void teacherController(char *teacherUsername) {

    do {
        int selectedOption = getTeacherOption() ;

        showOptionHeader() ;
        switch (selectedOption) {

            case GENERATE_AGENDA :
                generateAgenda(teacherUsername) ;
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