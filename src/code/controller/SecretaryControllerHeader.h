#pragma once

#include "../model/Student.h"
#include "../view/SecretaryViewHeader.h"
#include "../db/SecretaryDBHeader.h"
#include "../view/CommonViewHeader.h"
#include <stdio.h>

enum SecretaryOption {
    ADD_STUDENT = 0,
    ADD_JOIN_ACTIVITY ,
    BOOK_LESSON,
    ADD_ABSENCE,
    COURSE_ABSENCE_REPORT,
    FREE_TEACHER_REPORT,
    SECRETARY_QUIT
} ;

void secretaryController() ;