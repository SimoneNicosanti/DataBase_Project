#pragma once


#define TEACHER_NAME_MAX_LENGHT 100
#define TEACHER_ADDRESS_MAX_LENGHT 100
#define TEACHER_NATIONALITY_MAX_LENGHT 100 

typedef struct {
    char teacherName[TEACHER_NAME_MAX_LENGHT + 1] ;
    char teacherNationality[TEACHER_ADDRESS_MAX_LENGHT + 1] ;
    char teacherAddress[TEACHER_NATIONALITY_MAX_LENGHT + 1] ;
} Teacher ;