#pragma once

#include "Class.h"


#define TEACHER_NAME_MAX_LEN 100 + 1
#define TEACHER_ADDRESS_MAX_LEN 100 + 1
#define TEACHER_NATIONALITY_MAX_LEN 100 + 1

typedef struct {
    char teacherName[TEACHER_NAME_MAX_LEN] ;
    char teacherNationality[TEACHER_ADDRESS_MAX_LEN] ;
    char teacherAddress[TEACHER_NATIONALITY_MAX_LEN] ;
} Teacher ;

typedef struct {
    char teacherName[TEACHER_NAME_MAX_LEN] ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    int classCode ;
} Teaching ;