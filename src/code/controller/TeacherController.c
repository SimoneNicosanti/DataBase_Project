#include "TeacherControllerHeader.h"


void generateAgenda(char *teacherUsername) {
    int weekIndex ;
    if (!getAgendaInfo(&weekIndex)) return ;

        // Esecuzione DB
    DatabaseResult *result = generateAgendaFromDatabase(teacherUsername, weekIndex) ;

    if (result == NULL) return ;

    char *header[] = {"Data", "Inizio", "Fine", "Tipo", "Codice Corso", "Livello Corso", "Allievo"} ;
    enum TableFieldType types[] = {DATE, TIME, TIME, STRING, INT, STRING, STRING} ;
    Table *table = createTable(result->numRows, 7, header, types) ;

    for (int i = 0 ; i < result->numRows ; i++) {
        GeneralLesson *lesson = (GeneralLesson *) result->rowsSet[i] ;
        setTableElem(table, i, 0, &(lesson->lessonDate)) ;
        setTableElem(table, i, 1, &(lesson->startTime)) ;
        setTableElem(table, i, 2, &(lesson->endTime)) ;
        setTableElem(table, i, 3, &(lesson->lessonType)) ;
        if (lesson->lessonType == COURSE) {
            setTableElem(table, i, 3, "C") ;
            setTableElem(table, i, 4, &(lesson->classCode)) ;
            setTableElem(table, i, 5, lesson->levelName) ;
            setTableElem(table, i, 6, "****") ;
        }
        else {
            int notCourse = -1 ;
            setTableElem(table, i, 3, "P") ;
            setTableElem(table, i, 4, &notCourse) ;
            setTableElem(table, i, 5, "****") ;
            setTableElem(table, i, 6, lesson->studentName) ;
        }
    }

    printTable(table) ;
    freeTable(table) ;

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