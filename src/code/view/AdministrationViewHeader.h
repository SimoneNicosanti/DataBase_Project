#pragma once

#include <stdbool.h>
#include "CommonViewHeader.h"
 
int getAdministrationOption() ;

bool getLevelInfo(Level *levelPtr) ;

bool getClassInfo(Class *classPtr) ;

bool getTeacherInfo(Teacher *teacherPtr) ;

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