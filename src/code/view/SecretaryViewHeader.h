#pragma once

#include "../model/Student.h"
#include "../utils/IOUtils.h"
#include "ViewUtilsHeader.h"
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "../model/Lesson.h"

int getSecretaryOption() ;

bool getStudentInfo(Student *studentPtr) ;

bool getStudentJoinActivityInfo(char *studentName, int *activityCodePtr) ;

bool getPrivateLessonInfo(PrivateLesson *lessonPtr) ;