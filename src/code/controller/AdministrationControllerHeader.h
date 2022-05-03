#pragma once

#include <stdbool.h>

#define LEVEL_NAME_MAX_LEN 45
#define LEVEL_BOOK_NAME_MAX_LEN 45

typedef struct {
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char levelBookName[LEVEL_BOOK_NAME_MAX_LEN] ;
    bool levelHasExam ;
} Level ;

void administrationController() ;