#pragma once

#include "../model/Student.h"
#include "../view/SecretaryViewHeader.h"
#include <stdio.h>

enum SecretaryOption {
    ADD_STUDENT = 0,
    QUIT
} ;

void secretaryController() ;