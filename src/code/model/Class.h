#pragma once


#include "Level.h"
#include "../utils/TimeUtils.h"

typedef struct {
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    Date activationDate ;
    int studentsNumber ; 
} Class ;

