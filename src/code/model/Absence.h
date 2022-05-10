#pragma once

#include "Student.h"
#include "Lesson.h"

typedef struct {
    int absenceCode ;
    Date absenceDate ;
    char studentName[STUDENT_NAME_MAX_LEN + 1] ;
    enum DayOfWeek dayOfWeek ;
    Time startTime ;
    int classCode ;
    char classLevel[LEVEL_NAME_MAX_LEN + 1] ;
} Absence ;
