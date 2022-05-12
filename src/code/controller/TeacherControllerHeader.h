#pragma once

#include "../model/Teacher.h"
#include "../model/Lesson.h"

#include "../view/TeacherViewHeader.h"
#include "../view/ViewUtilsHeader.h"
#include "../view/TablePrinterHeader.h"
#include "../db/TeacherDBHeader.h"

enum TeacherOptions {
    GENERATE_AGENDA = 0,
    TEACHER_QUIT
} ;


void teacherController(char *teacherUsername) ;