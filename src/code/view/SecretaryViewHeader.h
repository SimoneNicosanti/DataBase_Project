#pragma once

#include "../model/Student.h"
#include "../utils/IOUtils.h"
#include "ViewUtilsHeader.h"
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "../model/Lesson.h"
#include "../model/Absence.h"
#include "../model/Partecipation.h"
#include "../model/Activity.h"
#include "../model/Class.h"
#include "TablePrinterHeader.h"

int getSecretaryOption() ;

bool getStudentInfo(Student *studentPtr) ;

bool getStudentJoinActivityInfo(char *studentName, int *activityCodePtr) ;

bool getPrivateLessonInfo(PrivateLesson *lessonPtr) ;

bool getCourseAbsenceReportInfo(char *levelName, int *courseCode) ;

bool getAbsenceInfo(Absence *absencePtr) ;

bool getFreeTeacherReportInfo(Date *datePtr, Time *timePtr, int *durationPtr) ;

bool getActivityParticipantsReportInfo(int *activityCode) ;

void printActivityParticipantsReport(Partecipation **partecipationArray, int arrayLen) ;

void printFreeTeacherReport(char **teacherNameArray, int arrayLen) ;

void printCourseAbsenceReport(Student **studentArray, int arrayLen) ;

void printAllActivities(CuturalActivity **activityArray, int arrayLen) ;

void printAllCourses(Class **classArray, int arrayLen) ;