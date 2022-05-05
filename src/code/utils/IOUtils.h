#pragma once

#include <stdbool.h>
#include "TimeUtils.h"

#define RED_TEXT_MARK 31 
#define GREEN_TEXT_MARK 32 

#define RED_HIGH_TEXT_MARK 41
#define GREEN_HIGH_TEXT_MARK 42

typedef enum {
    RED_TEXT ,
    GREEN_TEXT ,
    RED_HIGH ,
    GREEN_HIGH 
} TextColorEnum ;


bool getUserInput(char *requestString, char *inputBuffer, int inputMaxSize) ;

bool getDateFromUser(Date *datePtr, char *requestString) ;

void colorPrint(char *printText, TextColorEnum colorEnum) ;

void printError(char *errorMessage) ;
