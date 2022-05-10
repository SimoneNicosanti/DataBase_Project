#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"
#include "../utils/SystemUtilsHeader.h"

#include "../model/Activity.h"
#include "../model/Class.h"
#include "../model/Level.h"
#include "../model/Student.h"
#include "../model/Teacher.h"
#include "../model/Lesson.h"

bool addLevelToDatabase(Level *levelPtr) ;

bool addClassToDatabase(Class *classPtr) ;

bool addTeacherToDatabase(Teacher *teacherPtr) ;

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) ;

bool organizeActivityInDatabase(CuturalActivity *newActivity) ;

bool addClassLessonToDatabase(ClassLesson *newLesson) ;

Teaching **selectAllTeaching() ;