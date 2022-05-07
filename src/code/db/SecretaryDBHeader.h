#include "Connector.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include <string.h>


#include "../model/Student.h"

bool addStudentToDatabase(Student *studentPtr) ;

bool addStudentJoinActivityToDatabase(char *studentName, int *activityCode) ;


typedef struct {
    Class **allClasses ;
    int classNumber ;
} ClassReport ;

ClassReport *retrieveAllClasses() ;


