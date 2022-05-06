#pragma once

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../code/utils/IOUtils.h"
#include "../code/utils/TimeUtils.h"
#include "../code/config/EnvironmentSetter.h"
#include "../code/db/Connector.h"
#include "../code/db/DatabaseLoginHeader.h"
#include "../code/db/DatabaseUtilsHeader.h"
#include "../code/controller/AdministrationControllerHeader.h"
#include "../code/db/AdministrationDatabaseHeader.h"
#include "../code/db/SecretaryDBHeader.h"

#include "../code/view/TablePrinterHeader.h"


#define SUCCESS_STRING "SUCCESSO"
#define FAILURE_STRING "FALLIMENTO"


void printSuccess() {
    colorPrint(SUCCESS_STRING, GREEN_HIGH) ; 
    printf("\n\n") ; 
}

void printFailure() {
    colorPrint(FAILURE_STRING, RED_HIGH) ;
    printf("\n\n") ;
}
