#pragma once


#define LEVEL_NAME_MAX_LEN 45 + 1
#define LEVEL_BOOK_NAME_MAX_LEN 45 + 1

typedef struct {
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char levelBookName[LEVEL_BOOK_NAME_MAX_LEN] ;
    short int levelHasExam ;
} Level ;
