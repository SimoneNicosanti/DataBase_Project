#include "TeacherViewHeader.h"


char *teacherMenuOptions[] = {"Generazione Agenda", "Quit"} ;

int getTeacherOption() {
    return getUserOption(teacherMenuOptions, 2) ;
}

bool getAgendaInfo(int *weekIndexPtr) {
    printOptionTitle(teacherMenuOptions[0]) ;
    if (!getIntegerFromUser(weekIndexPtr, "Inserire Indice Settimana [0=attuale, 1=prossima, 2=due settimane ecc] >>> ")) {
        printError("Errore Lettura Indice Settimana") ;
        return false ;
    }

    return true ;
}

void printAgenda(GeneralLesson **lessonArray, int arrayLen) {
    char *header[] = {"Data", "Inizio", "Fine", "Tipo", "Codice Corso", "Livello Corso", "Allievo"} ;
    enum TableFieldType types[] = {DATE, TIME, TIME, STRING, INT, STRING, STRING} ;
    Table *table = createTable(arrayLen, 7, header, types) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        GeneralLesson *lesson = lessonArray[i] ;
        setTableElem(table, i, 0, &(lesson->lessonDate)) ;
        setTableElem(table, i, 1, &(lesson->startTime)) ;
        setTableElem(table, i, 2, &(lesson->endTime)) ;
        setTableElem(table, i, 3, &(lesson->lessonType)) ;
        if (lesson->lessonType == COURSE) {
            setTableElem(table, i, 3, "Corso") ;
            setTableElem(table, i, 4, &(lesson->classCode)) ;
            setTableElem(table, i, 5, lesson->levelName) ;
            setTableElem(table, i, 6, NULL) ;
        }
        else {
            setTableElem(table, i, 3, "Privata") ;
            setTableElem(table, i, 4, NULL) ;
            setTableElem(table, i, 5, NULL) ;
            setTableElem(table, i, 6, lesson->studentName) ;
        }
    }

    printTable(table) ;
    freeTable(table) ;
    printf("\n") ;
}