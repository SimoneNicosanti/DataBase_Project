#include "TeacherControllerHeader.h"


void generateAgenda(char *teacherUsername) {
    int weekIndex ;
    if (!getAgendaInfo(&weekIndex)) return ;

    // Esecuzione DB
    DatabaseResult **resultArray = generateAgendaFromDatabase(teacherUsername, weekIndex) ;
    
    if (resultArray == NULL) return ;

    for (int i = 0 ; i < 7 ; i++) {
        if (resultArray[i] == NULL) break ;
        DatabaseResult * result = resultArray[i] ;
        printAgenda((GeneralLesson **) result->rowsSet, result->numRows) ;
        freeDatabaseResult(result) ;
    }
    
    free(resultArray) ;
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