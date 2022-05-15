#pragma once

#include "Student.h"

typedef struct {
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    char studentTelephone[STUDENT_TELEPHONE_MAX_LEN + 1] ;
    int activityCode ;
} Partecipation ;