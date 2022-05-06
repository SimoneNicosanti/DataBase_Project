#pragma once

#include "../model/Student.h"
#include "../view/SecretaryViewHeader.h"
#include "../db/SecretaryDBHeader.h"
#include <stdio.h>

enum SecretaryOption {
    ADD_STUDENT = 0,
    ADD_JOIN_ACTIVITY ,
    QUIT
} ;

void secretaryController() ;