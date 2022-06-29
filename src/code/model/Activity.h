#pragma once

#include "../utils/TimeUtils.h"

enum ActivityType {
    FILM = 0,
    MEETING
} ;

#define FILM_TITLE_MAX_LEN 100 + 1
#define FILM_DIRECTOR_NAME_MAX_LEN 100 + 1
#define MEETING_LECTURER_NAME_MAX_LEN 100 + 1
#define MEETING_ARGUMENT_MAX_LEN 100 + 1

typedef struct {
    int activityCode ;
    Date activityDate ;
    Time activityTime ;
    enum ActivityType type ;
    char filmTitle[FILM_TITLE_MAX_LEN] ;
    char filmDirector[FILM_DIRECTOR_NAME_MAX_LEN] ;
    char meetingLecturer[MEETING_LECTURER_NAME_MAX_LEN] ;
    char meetingArgument[MEETING_ARGUMENT_MAX_LEN] ;
} CuturalActivity ;


