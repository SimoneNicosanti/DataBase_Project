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


typedef struct {
    Class **allClasses ;
    int classNumber ;
} ClassReport ;

typedef struct {
    CuturalActivity **allActivities ;
    int number ;
} ActivitiesReport ;

ClassReport *retrieveAllClasses() ;

ActivitiesReport *getAllActivitiesFromDatabase() ;

bool addAbsenceToDatabase(Absence *newAbsence) ;


