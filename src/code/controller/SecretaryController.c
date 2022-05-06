#include "SecretaryControllerHeader.h"


void addStudent() {
    Student newStudent ;
    if (getStudentInfo(&newStudent)) {
        addStudentToDatabase(&newStudent) ; 
    }
}

void addStudentJoinActivity() {
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    int activityCode ;
    if (getStudentJoinActivityInfo(studentName, &activityCode)) {
        addStudentJoinActivityToDatabase(studentName, &activityCode) ;
    }
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

            case QUIT :
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