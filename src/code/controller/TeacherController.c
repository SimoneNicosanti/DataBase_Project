#include "TeacherControllerHeader.h"


void generateAgenda(char *teacherUsername) {
    int weekIndex ;
    if (!getAgendaInfo(&weekIndex)) return ;

    // Esecuzione DB
    DatabaseResult *result = generateAgendaFromDatabase(teacherUsername, weekIndex) ;
    
    if (result == NULL) return ;

    printAgenda((GeneralLesson **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
}


void teacherController(char *teacherUsername) {

    do {
        int selectedOption = getTeacherOption() ;

        showOptionHeader() ;
        switch (selectedOption) {

            case GENERATE_AGENDA :
                generateAgenda(teacherUsername) ;
                break ;

            case TEACHER_QUIT :
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