#include <stdbool.h>
#include <string.h>

#include "../controller/AdministrationControllerHeader.h"

#include "../utils/SystemUtilsHeader.h"
#include "../utils/IOUtils.h"

#include "../model/Activity.h"
#include "../model/Class.h"
#include "../model/Level.h"
#include "../model/Student.h"
#include "../model/Teacher.h"
#include "../model/Lesson.h"
#include "../model/User.h"

#include "Connector.h"
#include "DatabaseUtilsHeader.h"


bool addLevelToDatabase(Level *levelPtr) ;

int *addClassToDatabase(Class *classPtr) ;

bool addTeacherToDatabase(Teacher *teacherPtr, char *username) ;

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) ;

int *organizeActivityInDatabase(CuturalActivity *newActivity) ;

bool addClassLessonToDatabase(ClassLesson *newLesson) ;

DatabaseResult *selectAllTeaching() ;

DatabaseResult *generateTeacherReportFromDB(char *teacherName, int *year, int *monthIndex) ;

bool restartYearDB() ;

DatabaseResult *selectAllLevels() ;

bool createUserDB(User *newUser, Role userRole) ;

DatabaseResult *selectAllTeachers() ;