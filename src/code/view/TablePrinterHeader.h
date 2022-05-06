#pragma once

#include <stdio.h>
#include <string.h>

typedef struct {
    char **headerArray ;
    char ***tableRows ;
    int rowsNum ;
    int colsNum ;
} Table ;


void printTable(Table *tablePtr) ; 