#pragma once

#include <stdio.h>
#include <string.h>
#include "../utils/TimeUtils.h"
#include "../utils/SystemUtilsHeader.h"

enum TableFieldType {
    STRING = 0,
    INT,
    DATE,
    TIME,
    FLOAT
} ;

typedef struct {
    int rowsNum ;
    int colsNum ;
    char **headerArray ;
    void ***table ;
    enum TableFieldType *rowStruct ;
} Table ;


void printTable(Table *tablePtr) ; 

Table *createTable(int rowsNum, int colsNum, char **headerArray, enum TableFieldType *rowTypes) ;

void freeTable(Table *tablePtr) ;

void setTableElem(Table *tablePtr, int rowIndex, int colIndex, void *elemPtr) ;