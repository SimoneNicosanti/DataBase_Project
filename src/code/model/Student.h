#pragma once

#include "Class.h"
#include "../utils/TimeUtils.h"

#define STUDENT_NAME_MAX_LEN 100 + 1
#define STUDENT_TELEPHONE_MAX_LEN 10 + 1


typedef struct {
    char studentName[STUDENT_NAME_MAX_LEN] ;
    char studentTelephone[STUDENT_TELEPHONE_MAX_LEN] ;
    int studentAbsenceNumber ;
    Date studentSubscribeDate ;
    Class studentClass ;
} Student ;