#pragma once

#include "Connector.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include <string.h>
#include "../utils/SystemUtilsHeader.h"


#include "../model/Student.h"
#include "../model/Activity.h"
#include "../model/Absence.h"

bool addStudentToDatabase(Student *studentPtr) ;

bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) ;



Class **retrieveAllClasses() ;

CuturalActivity **getAllActivitiesFromDatabase() ;

bool addAbsenceToDatabase(Absence *newAbsence) ;


bool bookPrivateLessonInDatabase(PrivateLesson *privateLesson) ;

Student **getCourseAbsenceReportDB(char *levelName, int courseCode) ;

