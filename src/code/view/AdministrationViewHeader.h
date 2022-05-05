#pragma once

#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"

int getAdministrationOption() ;

bool getLevelInfo(Level *levelPtr) ;

bool getClassInfo(Class *classPtr) ;

bool getTeacherInfo(Teacher *teacherPtr) ;

bool getTeacherAndClassInfo(Teacher *teacherPtr, Class *classPtr) ;

bool getActivityInfo(CuturalActivity *activityPtr) ;