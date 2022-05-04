#pragma once

#include <stdbool.h>
#include <time.h>

#include "../utils/TimeUtils.h"

#define LEVEL_NAME_MAX_LEN 45
#define LEVEL_BOOK_NAME_MAX_LEN 45

typedef struct {
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    char levelBookName[LEVEL_BOOK_NAME_MAX_LEN + 1] ;
    short int levelHasExam ;
} Level ;

typedef struct {
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    Date activationDate ;
    int studentsNumber ; 
} Class ;


#define TEACHER_NAME_MAX_LENGHT 100
#define TEACHER_ADDRESS_MAX_LENGHT 100
#define TEACHER_NATIONALITY_MAX_LENGHT 100 
typedef struct {
    char teacherName[TEACHER_NAME_MAX_LENGHT + 1] ;
    char teacherNationality[TEACHER_ADDRESS_MAX_LENGHT + 1] ;
    char teacherAddress[TEACHER_NATIONALITY_MAX_LENGHT + 1] ;
} Teacher ;


enum ActivityType {
    FILM = 0,
    MEETING
} ;

#define FILM_TITLE_MAX_SIZE 100 
#define FILM_DIRECTOR_NAME_MAX_SIZE 100
#define MEETING_LECTURER_NAME_MAX_SIZE 100
#define MEETING_ARGUMENT_MAX_SIZE 100
typedef struct {
    int activityCode ;
    Date activityDate ;
    Time activityTime ;
    enum ActivityType type ;
    char filmTitle[FILM_TITLE_MAX_SIZE + 1] ;
    char filmDirector[FILM_DIRECTOR_NAME_MAX_SIZE + 1] ;
    char meetingLecturer[MEETING_LECTURER_NAME_MAX_SIZE + 1] ;
    char meetingArgument[MEETING_ARGUMENT_MAX_SIZE + 1] ;
} CuturalActivity ;

void administrationController() ;