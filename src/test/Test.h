#pragma once

#define SUCCESS_STRING "SUCCESSO"
#define FAILURE_STRING "FALLIMENTO"

#include "../code/utils/IOUtils.h"
#include <stdio.h>

#include <string.h>

#include "../code/config/EnvironmentSetter.h"
#include "../code/db/Connector.h"
#include "../code/db/DatabaseLoginHeader.h"
#include "../code/db/DatabaseUtilsHeader.h"

void printSuccess() {
    colorPrint(SUCCESS_STRING, GREEN_HIGH) ; 
    printf("\n\n") ; 
}

void printFailure() {
    colorPrint(FAILURE_STRING, RED_HIGH) ;
    printf("\n\n") ;
}