#include <stdbool.h>
#include "../controller/AdministrationControllerHeader.h"

bool addLevelToDatabase(Level *levelPtr) ;

bool addClassToDatabase(Class *classPtr) ;

bool addTeacherToDatabase(Teacher *teacherPtr) ;

bool assignTeacherToClass(Teacher *teacherPtr, Class *classPtr) ;

bool organizeActivityInDatabase(CuturalActivity *newActivity) ;