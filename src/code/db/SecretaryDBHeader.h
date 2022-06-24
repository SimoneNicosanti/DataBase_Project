#pragma once

#include "Connector.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include <string.h>
#include "../utils/SystemUtilsHeader.h"


#include "../model/Student.h"
#include "../model/Activity.h"
#include "../model/Absence.h"
#include "../model/Partecipation.h"

bool addStudentToDatabase(Student *studentPtr) ;

bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) ;


 
DatabaseResult *selectAllCourses() ;

DatabaseResult *getAllActivitiesFromDatabase() ;

bool addAbsenceToDatabase(Absence *newAbsence) ;


bool bookPrivateLessonInDatabase(PrivateLesson *privateLesson) ;

DatabaseResult *getCourseAbsenceReportDB(char *levelName, int courseCode) ;

DatabaseResult *loadFreeTeachersFromDB(Date *date, Time *time, int *duration) ;