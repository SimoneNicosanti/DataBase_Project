#include "AdministrationControllerHeader.h"


enum AdministrationControllerOptions {
    ADD_LEVEL = 0,
    ADD_CLASS,
    ADD_TEACHER,
    ASSIGN_CLASS, 
    ADD_LESSON,
    ORGANIZE_ACTIVITY,
    ADMINISTRATION_QUIT,
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

void printAllTeaching(DatabaseResult *result) {

    char *header[] = {"Codice Corso", "Livello Corso", "Nome Insegnante"} ;
    enum TableFieldType types[] = {INT, STRING, STRING} ;
    Table *table = createTable(result->numRows, 3, header, types) ;

    for (int i = 0 ; i < result->numRows ; i++) {
        Teaching *teaching = (Teaching *) result->rowsSet[i] ;
        setTableElem(table, i, 0, &(teaching->classCode)) ;
        setTableElem(table, i, 1, teaching->levelName) ;
        setTableElem(table, i, 2, teaching->teacherName) ;
    }

    printTable(table) ;
    freeTable(table) ;

    freeDatabaseResult(result) ;
}

void addLesson() {
    DatabaseResult *result = selectAllTeaching() ;
    if (result != NULL) printAllTeaching(result) ;
    ClassLesson newLesson ;
    if (getCourseLessonInfo(&newLesson)) {
        addClassLessonToDatabase(&newLesson) ;
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

            case ADD_LESSON :
                addLesson() ;
                break ;

            case ORGANIZE_ACTIVITY :
                organizeActivity() ;
                break ;
        
            case ADMINISTRATION_QUIT :
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