#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/SystemUtilsHeader.h"
#include "ViewUtilsHeader.h"
#include "../utils/IOUtils.h"
#include "../model/Lesson.h"
#include "TablePrinterHeader.h"


int getTeacherOption() ;

bool getAgendaInfo(int *weekIndexPtr) ;

void printAgenda(GeneralLesson **lessonArray, int arrayLen) ;