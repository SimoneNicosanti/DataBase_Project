#pragma once

#include <stdbool.h>
#include <time.h>

#include "../utils/TimeUtils.h"

#define LEVEL_NAME_MAX_LEN 45
#define LEVEL_BOOK_NAME_MAX_LEN 45

typedef struct {
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    char levelBookName[LEVEL_BOOK_NAME_MAX_LEN + 1] ;
    short int levelHasExam ;
} Level ;

typedef struct {
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    Date activationDate ;
    int studentsNumber ; 
} Class ;

void administrationController() ;