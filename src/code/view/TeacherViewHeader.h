#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"

#include "ViewUtilsHeader.h"
#include "TablePrinterHeader.h"

#include "../model/Lesson.h"


int getTeacherOption() ;

bool getAgendaInfo(int *weekIndexPtr) ;

void printAgenda(GeneralLesson **lessonArray, int arrayLen) ;