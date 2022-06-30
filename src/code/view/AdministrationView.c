#include "AdministrationViewHeader.h"



char *administrationMenuOptions[] = {
    "Aggiungi Livello", 
    "Aggiungi Corso", 
    "Aggiungi Insegnante", 
    "Assegna Corso", 
    "Aggiungi Lezione Corso",
    "Organizza Attività",
    "Report Insegnante" ,
    "Riavvio Anno Scolastico",
    "Quit"
    } ;


int getAdministrationOption() {
    return getUserOption(administrationMenuOptions, 9) ;
}

bool getLevelInfo(Level *levelPtr) {
    printOptionTitle(administrationMenuOptions[0]) ;
    
    if (!getUserInput("Inserire Nome Livello >>> ", levelPtr->levelName, LEVEL_NAME_MAX_LEN)) {
        printError("Errore Lettura Nome Livello") ;
        return false ;
    }
    if (!getUserInput("Inserire Nome Libro >>> ", levelPtr->levelBookName, LEVEL_BOOK_NAME_MAX_LEN)) {
        printError("Errore Lettura Nome Libro") ;
        return false ;
    }

    char hasExamString[2] ;
    if (!getUserInput("Il Livello Ha Un Esame?? [y-n] >>> ", hasExamString, 2)) {
        printError("Errore Lettura Esame") ;
        return false ;
    }

    if (strcmp(hasExamString, "y") == 0) {
            levelPtr->levelHasExam = true ;
            printf("ESAME\n") ;
        }
    else if (strcmp(hasExamString, "n") == 0) levelPtr->levelHasExam = false ;
    else {
        printError("Opzione Inserita NON Valida") ;
        return false ;
    }

    return true ;
}


bool getClassInfo(Class *classPtr) {
    printOptionTitle(administrationMenuOptions[1]) ;

    if (!(getUserInput("Inserire Livello del Nuovo Corso >>> ", classPtr->levelName, LEVEL_NAME_MAX_LEN))) {
        printError("Errore Inserimento Nome Livello") ;
        return false ;
    }

    if (!getDateFromUser(&(classPtr->activationDate), "Inserire Data Attivazione Nuovo Corso [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    return true ;
}

bool getTeacherInfo(Teacher *teacherPtr, char *teacherUsername) {
    printOptionTitle(administrationMenuOptions[2]) ;

    if (!getUserInput("Inserire Nome Insegnante >>> ", teacherPtr->teacherName, TEACHER_NAME_MAX_LEN)) {
        printError("Errore Inserimento Nome Insegnante") ;
        return false ;
    }

    if (!getUserInput("Inserire Nazionalità Insegnante >>> ", teacherPtr->teacherNationality, TEACHER_NATIONALITY_MAX_LEN)) {
        printError("Errore Inserimento Nazionalità") ;
        return false ;
    }

    if (!getUserInput("Inserire Indirizzo Insegnante >>> ", teacherPtr->teacherAddress, TEACHER_ADDRESS_MAX_LEN)) {
        printError("Errore Inserimento Indirizzo") ;
        return false ;
    }

    if (!getUserInput("Inserire Username Insegnante >>> ", teacherUsername, USERNAME_MAX_SIZE)) {
        printError("Errore Inserimento Username") ;
        return false ;
    }

    return true ;
}

bool getTeacherAndClassInfo(Teacher *teacherPtr, Class *classPtr) {
    printOptionTitle(administrationMenuOptions[3]) ;

    if (!getUserInput("Inserire Nome Insegnante >>> ", teacherPtr->teacherName, TEACHER_NAME_MAX_LEN)) {
        printError("Errore Inserimento Nome Insegnante") ;
        return false ;
    }

    if (!getIntegerFromUser(&(classPtr->classCode), "Inserire Codice Corso >>> ")) {
        printError("Errore Lettura Codice Corso") ;
        return false ;
    }

    return true ;
}


bool getActivityInfo(CuturalActivity *activityPtr) {
    printOptionTitle(administrationMenuOptions[4]) ;

    char activityTypeString[2] ;
    if (!getUserInput("Inserire Tipo Di Attivita [P-C] >>> ", activityTypeString, 2)) {
        printError("Errore Inserimento Tipo Attività") ;
        return false ;
    }

    if (strcmp(activityTypeString, "P") != 0 && strcmp(activityTypeString, "C") != 0) {
        printError("Tipo di Attività Non Valido") ;
        return false ;
    }

    if (strcmp(activityTypeString, "P") == 0) {
        activityPtr->type = FILM ;

        if (!getUserInput("Inserire Titolo Film >>> ", activityPtr->filmTitle, FILM_TITLE_MAX_LEN)) {
            printError("Errore Inserimento Titolo Film") ;
            return false ;
        }
        if (!getUserInput("Inserire Regista Film >>> ", activityPtr->filmDirector, FILM_DIRECTOR_NAME_MAX_LEN)) {
            printError("Errore Inserimento Regista Film") ;
            return false ;
        }
    }
    else {
        activityPtr->type = MEETING ;

        if (!getUserInput("Inserire Nome Conferenziere >>> ", activityPtr->meetingLecturer, MEETING_LECTURER_NAME_MAX_LEN)) {
            printError("Errore Inserimento Conferenziere") ;
            return false ;
        }
        if (!getUserInput("Inserire Argomento Conferenza >>> ", activityPtr->meetingArgument, MEETING_ARGUMENT_MAX_LEN)) {
            printError("Errore Inserimento Argomento Conferenza") ;
            return false ;
        }
    }

    if (!getDateFromUser(&(activityPtr->activityDate), "Inserire Data Attività [yyyy-mm-dd] >>> ")) {
        return false ;
    }

    if (!getTimeFromUser(&(activityPtr->activityTime), "Inserire Orario Attività [hh:mm] >>> ")) {
        return false ;
    }

    return true ;

} 

bool getCourseLessonInfo(ClassLesson *newLesson) {
    printOptionTitle("Inserimento Lezione Corso") ;
    
    if (!getTimeFromUser(&(newLesson->startTime), "Inserire Orario Inizio Lezione [hh:mm] >>> ")) {
        printError("Errore Presa Data") ;
        return false ;
    }

    if (!getIntegerFromUser(&(newLesson->lessonDuration), "Inserire Durata Lezione In Minuti >>> ")) {
        printError("Impossibile Prendere Durata Lezione") ;
        return false ;
    }

    if (!getUserInput("Inserire Nome Insegnante >>> ", newLesson->teacherName,  TEACHER_NAME_MAX_LEN)) {
        printError("Impossibile Prendere Nome Insegnante") ;
        return false ;
    }

    if (!getUserInput("Inserire Nome Livello >>> ", newLesson->classLevel,  LEVEL_NAME_MAX_LEN)) {
        printError("Impossibile Leggere Nome Livello") ;
        return false ;
    }

    if (!getIntegerFromUser(&(newLesson->classCode), "Inserire Codice Corso >>> ")) {
        printError("Impossibile Leggere Codice Corso") ;
        return false ;
    }

    char dayOfWeekStr[3 + 1] ;
    if (!getUserInput("Inserire Giorno Settimana [Lun-Mar-Mer-Gio-Ven-Sab-Dom] >>> ", dayOfWeekStr, 4)) {
        printError("Errore Lettura Giorno della Settimana") ;
        return false ;
    }

    if (!(strcmp(dayOfWeekStr, "Lun") || strcmp(dayOfWeekStr, "Mar") || strcmp(dayOfWeekStr, "Mer") || strcmp(dayOfWeekStr, "Gio") || strcmp(dayOfWeekStr, "Ven") || strcmp(dayOfWeekStr, "Sab") || strcmp(dayOfWeekStr, "Dom"))) {
        printError("Errore Giorno Settimana Inserito") ;
        return false ;
    }

    return true ;
}

 
bool getTeacherReportInfo(char *teacherName, int *yearPtr, int *monthIndexPtr) {
    if (!getUserInput("Inserire Nome Insegnante >>> ", teacherName, TEACHER_NAME_MAX_LEN)) {
        printError("Errore Lettura Nome Insegnante") ;
        return false ;
    }

    if (!getIntegerFromUser(yearPtr, "Inserire Anno >>> ")) {
        printError("Errore Lettura Anno") ;
        return false ;
    }

    if (!getIntegerFromUser(monthIndexPtr, "Inserire Indice Mese [0=Gen , 1=Feb , 2=Mar ecc] >>> ")) {
        printError("Errore Lettura Indice Mese") ;
        return false ;
    }

    return true ;
}


void printTeacherReport(ReportLesson **lessonArray, int arrayLen) {
    char *header[] = {"Data Lezione", "Orario Inizio", "Durata", "Tipo Lezione"} ;
    enum TableFieldType types[] = {DATE, TIME, INT, STRING} ;
    Table *table = createTable(arrayLen, 4, header, types) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        ReportLesson *lesson = lessonArray[i] ;
        setTableElem(table, i, 0, &(lesson->lessonDate)) ;
        setTableElem(table, i, 1, &(lesson->startTime)) ;
        setTableElem(table, i, 2, &(lesson->duration)) ;
        setTableElem(table, i, 3, (lesson->lessonType == COURSE) ? "Corso" : "Privata") ;
    }

    printTable(table) ;
    freeTable(table) ;
}

void printAllTeaching(Teaching **teachingArray, int arrayLen) {
    char *header[] = {"Codice Corso", "Livello Corso", "Nome Insegnante"} ;
    enum TableFieldType types[] = {INT, STRING, STRING} ;
    Table *table = createTable(arrayLen, 3, header, types) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        Teaching *teaching = teachingArray[i] ;
        setTableElem(table, i, 0, &(teaching->classCode)) ;
        setTableElem(table, i, 1, teaching->levelName) ;
        setTableElem(table, i, 2, teaching->teacherName) ;
    }

    printTable(table) ;
    freeTable(table) ;
}

void printNewClassCode(int *newClassCode) {
    char *header[] = {"Codice Nuovo Corso"} ;
    enum TableFieldType types[] = {INT} ;

    Table *table = createTable(1, 1, header, types) ;
    setTableElem(table, 0, 0, newClassCode) ;

    printTable(table) ;
    freeTable(table) ;
}

bool askRestartConfirm() {

    char confirm[2] ;
    if (!getUserInput("Confermi di voler riavviare l'anno scolastico [y-n] >>> ", confirm, 2)) {
        printError("Errore lettura conferma") ;
    }

    if (strcmp(confirm, "y") == 0) return true ;
    else return false ;
}
 

void printRestartSuccess() {
    printf("Riavvio Anno Avvenuto Con Successo") ;
}


void printAllLevels(Level **levelsArray , int num) {

    char *header[] = {"Nome Livello", "Esame"} ;
    enum TableFieldType types[] = {STRING, STRING} ;
    Table *table = createTable(num, 2, header, types) ;
    
    for (int i = 0 ; i < num ; i++) {
        Level *level = levelsArray[i] ;
        setTableElem(table, i, 0, level->levelName) ;
        
        if (level->levelHasExam == 1) setTableElem(table, i, 1, "SI") ;
        else setTableElem(table, i, 1, "NO") ;

    }

    printTable(table) ;
    freeTable(table) ;
}

void printAllCoursesAdministration(Class **classArray, int arrayLen) {
    printAllCourses(classArray, arrayLen) ;
}

void printAllTeachers(Teacher **teachersArray, int arrayLen) {
    
    char *header[] = {"Nome", "Nazione"} ;
    enum TableFieldType types[] = {STRING, STRING} ;
    Table *table = createTable(arrayLen, 2, header, types) ;

    for (int i = 0 ; i < arrayLen ; i++) {
        Teacher *teacher = teachersArray[i] ;
        setTableElem(table, i, 0, teacher->teacherName) ;
        setTableElem(table, i, 1, teacher->teacherNationality) ;
    }
    
    printTable(table) ;

    freeTable(table) ;
}