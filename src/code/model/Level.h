#pragma once


#define LEVEL_NAME_MAX_LEN 45
#define LEVEL_BOOK_NAME_MAX_LEN 45

typedef struct {
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    char levelBookName[LEVEL_BOOK_NAME_MAX_LEN + 1] ;
    int levelHasExam ;
} Level ;
