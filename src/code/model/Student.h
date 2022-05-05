#pragma once

#include "Class.h"
#include "../utils/TimeUtils.h"

#define STUDENT_NAME_MAX_LEN 100 
#define STUDENT_TELEPHONE_MAX_LEN 10

typedef struct {
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    char studentTelephone[STUDENT_TELEPHONE_MAX_LEN + 1] ;
    int studentAbsenceNumber ;
    Date studentSubscribeDate ;
    Class studentClass ;
} Student ;