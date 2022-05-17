#include "TeacherViewHeader.h"


char *teacherMenuOptions[] = {"Genera Agenda", "Quit"} ;

int getTeacherOption() {
    return getUserOption(teacherMenuOptions, 2) ;
}

bool getAgendaInfo(int *weekIndexPtr) {
    printOptionTitle("Generazione Agenda") ;
    if (!getIntegerFromUser(weekIndexPtr, "Inserire Indice Settimana [0=attuale, 1=prossima, 2=due settimane ecc] >>> ")) {
        printError("Errore Lettura Indice Settimana") ;
        return false ;
    }

    return true ;
}