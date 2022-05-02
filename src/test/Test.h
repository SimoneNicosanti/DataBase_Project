#define SUCCESS_STRING "SUCCESSO"
#define FAILURE_STRING "FALLIMENTO"

#include "../code/utils/IOUtils.h"

void printSuccess() {
    colorPrint(SUCCESS_STRING, GREEN_HIGH) ; 
    printf("\n\n") ; 
}

void printFailure() {
    colorPrint(FAILURE_STRING, RED_HIGH) ;
    printf("\n\n") ;
}