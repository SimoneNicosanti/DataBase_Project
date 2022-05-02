#pragma once

#include <stdbool.h>

typedef struct {
    char *username ;
    char *password ;
} LoginCredentials ;

void loginController() ;