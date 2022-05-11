#pragma once

#include "../model/Teacher.h"
#include "../model/Lesson.h"

#include "../view/TeacherViewHeader.h"
#include "../view/ViewUtilsHeader.h"
#include "../view/TablePrinterHeader.h"

enum TeacherOptions {
    GENERATE_AGENDA = 0,
    QUIT
} ;


void teacherController(char *teacherUsername) ;