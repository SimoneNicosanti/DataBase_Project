#pragma once

#include "Student.h"

typedef struct {
    char studentName[STUDENT_NAME_MAX_LEN] ;
    char studentTelephone[STUDENT_TELEPHONE_MAX_LEN] ;
    int activityCode ;
} Partecipation ;