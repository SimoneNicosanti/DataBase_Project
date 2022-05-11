#pragma once

#include "Connector.h"
#include "DatabaseUtilsHeader.h"

#include "../model/Lesson.h"
#include "../utils/SystemUtilsHeader.h"

GeneralLesson **generateAgendaFromDatabase(char *teacherUsername, int weekIndex) ;