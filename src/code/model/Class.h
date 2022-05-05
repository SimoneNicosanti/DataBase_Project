#pragma once


#include "Level.h"
#include "../utils/TimeUtils.h"

typedef struct {
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN + 1] ;
    Date activationDate ;
    int studentsNumber ; 
} Class ;