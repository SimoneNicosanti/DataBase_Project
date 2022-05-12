#include "TeacherControllerHeader.h"


void generateAgenda(char *teacherUsername) {
    int weekIndex ;
    if (getAgendaInfo(&weekIndex)) {
        // Esecuzione DB
        GeneralLesson **lessonArray = generateAgendaFromDatabase(teacherUsername, weekIndex) ;

        if (lessonArray == NULL) return ;

        int num = 0 ;
        while (lessonArray[num] != NULL) num++ ;

        char *header[] = {"Data", "Inizio", "Fine", "Tipo", "Codice Corso", "Livello Corso", "Allievo"} ;
        enum TableFieldType types[] = {DATE, TIME, TIME, STRING, INT, STRING, STRING} ;
        Table *table = createTable(num, 7, header, types) ;

        for (int i = 0 ; i < num ; i++) {
            GeneralLesson *lesson = lessonArray[i] ;
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