#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/SystemUtilsHeader.h"

#include "../model/Activity.h"
#include "../model/Class.h"
#include "../model/Level.h"
#include "../model/Student.h"
#include "../model/Teacher.h"
#include "../model/Lesson.h"

#include "Connector.h"
#include "../utils/IOUtils.h"
#include "DatabaseUtilsHeader.h"
#include <stdbool.h>
#include <string.h>

bool addLevelToDatabase(Level *levelPtr) ;

int *addClassToDatabase(Class *classPtr) ;

bool addTeacherToDatabase(Teacher *teacherPtr) ;

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) ;

bool organizeActivityInDatabase(CuturalActivity *newActivity) ;

bool addClassLessonToDatabase(ClassLesson *newLesson) ;

DatabaseResult *selectAllTeaching() ;

DatabaseResult *generateTeacherReportFromDB(char *teacherName, int *year, int *monthIndex) ;

bool restartYearDB() ;