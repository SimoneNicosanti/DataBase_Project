#pragma once

#include <stdbool.h>
#include "CommonViewHeader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ViewUtilsHeader.h"
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/IOUtils.h"
#include "../model/Lesson.h"
 
int getAdministrationOption() ;

bool getLevelInfo(Level *levelPtr) ;

bool getClassInfo(Class *classPtr) ;

bool getTeacherInfo(Teacher *teacherPtr, char *teacherUsername) ;

bool getTeacherAndClassInfo(Teacher *teacherPtr, Class *classPtr) ;

bool getActivityInfo(CuturalActivity *activityPtr) ;

bool getCourseLessonInfo(ClassLesson *newLesson) ;

bool getTeacherReportInfo(char *teacherName, int *year, int *monthIndex) ;

void printTeacherReport(ReportLesson **lessonArray, int arrayLen) ;

void printAllTeaching(Teaching **teachingArray, int arrayLen) ;

void printNewClassCode(int *newClassCode) ;

bool askRestartConfirm() ;

void printRestartSuccess() ;

void printAllLevels(Level **levelArray, int num) ;

void printAllCoursesAdministration(Class **classArray, int arrayLen) ;