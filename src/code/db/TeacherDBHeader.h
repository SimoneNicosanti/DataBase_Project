#pragma once

#include "Connector.h"
#include "DatabaseUtilsHeader.h"

#include "../model/Lesson.h"
#include "../utils/SystemUtilsHeader.h"

DatabaseResult **generateAgendaFromDatabase(char *teacherUsername, int weekIndex) ; 