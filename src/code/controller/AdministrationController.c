#include "AdministrationControllerHeader.h"

 
enum AdministrationControllerOptions {
    ADD_LEVEL = 0,
    ADD_CLASS,
    ADD_TEACHER,
    ASSIGN_CLASS, 
    ADD_LESSON,
    ORGANIZE_ACTIVITY,
    TEACHER_REPORT,
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
    if (!getClassInfo(&newClass)) return ;
    
    int *newClassCode = addClassToDatabase(&newClass) ;

    if (newClassCode == NULL) return ;

    printNewClassCode(newClassCode) ;

    free(newClassCode) ;
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

void getAllTeaching() {

    DatabaseResult *result = selectAllTeaching() ;
    if (result != NULL) return ;

    printAllTeaching((Teaching **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
}

void addLesson() {
    getAllTeaching() ;
    ClassLesson newLesson ;
    if (getCourseLessonInfo(&newLesson)) {
        addClassLessonToDatabase(&newLesson) ;
    }
}

void generateTeacherReport() {
    char teacherName[TEACHER_NAME_MAX_LEN + 1] ;
    int year ;
    int monthIndex ;

    if (!getTeacherReportInfo(teacherName, &year, &monthIndex)) return ;

    DatabaseResult *result = generateTeacherReportFromDB(teacherName, &year, &monthIndex) ;
    if (result == NULL) return ;

    printTeacherReport((ReportLesson **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
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

            case TEACHER_REPORT :
                generateTeacherReport() ;
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