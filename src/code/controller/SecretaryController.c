#include "SecretaryControllerHeader.h"

void getAllClasses() {
    DatabaseResult *result = selectAllCourses() ;
    if (result == NULL) return ;

    printAllCourses((Class **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
}

void addStudent() {
    getAllClasses() ;
    Student newStudent ;
    if (getStudentInfo(&newStudent)) {
        addStudentToDatabase(&newStudent) ; 
    }
} 

void getAllActivities() {
    DatabaseResult *result = getAllActivitiesFromDatabase() ;
    if (result == NULL) return ;
    printAllActivities((CuturalActivity **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
}

void addStudentJoinActivity() {
    getAllActivities() ;
    char studentName[STUDENT_NAME_MAX_LEN] ;
    int activityCode ;
    if (getStudentJoinActivityInfo(studentName, &activityCode)) {
        addStudentJoinActivityToDatabase(studentName, &activityCode) ;
    }
}


void bookPrivateLesson() {
    PrivateLesson privateLesson ;
    if (getPrivateLessonInfo(&privateLesson)) {
        bookPrivateLessonInDatabase(&privateLesson) ;
    }
}

void courseAbsenceReport() {
    getAllClasses() ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    int courseCode ;

    if (!getCourseAbsenceReportInfo(levelName, &courseCode)) return ;
   
    DatabaseResult *result = getCourseAbsenceReportDB(levelName, courseCode) ;

    if (result == NULL) return ;

    printCourseAbsenceReport((Student **) result->rowsSet, result->numRows) ;
    
    freeDatabaseResult(result) ;
}

void addAbsence() {
    Absence absence ;
    if (getAbsenceInfo(&absence)) {
        addAbsenceToDatabase(&absence) ;
    }
}

 
void freeTeacherReport() {
    Date date ;
    Time time ;
    int duration ;

    if (!getFreeTeacherReportInfo(&date, &time, &duration)) return ;
    
    DatabaseResult *result = loadFreeTeachersFromDB(&date, &time, &duration) ;
    if (result == NULL) return ;

    printFreeTeacherReport((char **) result->rowsSet, result->numRows) ;

    freeDatabaseResult(result) ;
}


void secretaryController() {

    do {
        int selectedOption = getSecretaryOption() ;

        showOptionHeader() ;
        switch (selectedOption) {

            case ADD_STUDENT :
                addStudent() ;
                break; ;

            case ADD_JOIN_ACTIVITY :
                addStudentJoinActivity() ;
                break ;

            case BOOK_LESSON :
                bookPrivateLesson() ;
                break ;

            case ADD_ABSENCE :
                addAbsence() ;
                break ;

            case COURSE_ABSENCE_REPORT :
                courseAbsenceReport() ;
                break ;
            
            case FREE_TEACHER_REPORT :
                freeTeacherReport() ;
                break ;

            case SECRETARY_QUIT :
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