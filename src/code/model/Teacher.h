#pragma once

#include "Class.h"


#define TEACHER_NAME_MAX_LENGHT 100
#define TEACHER_ADDRESS_MAX_LENGHT 100
#define TEACHER_NATIONALITY_MAX_LENGHT 100 

typedef struct {
    char teacherName[TEACHER_NAME_MAX_LENGHT + 1] ;
    char teacherNationality[TEACHER_ADDRESS_MAX_LENGHT + 1] ;
    char teacherAddress[TEACHER_NATIONALITY_MAX_LENGHT + 1] ;
} Teacher ;

typedef struct {
    char teacherName[TEACHER_NAME_MAX_LENGHT + 1] ;
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    int classCode ;
} Teaching ;