#include <stdio.h>
#include "TestUtils.h"

void printResponse(bool positive) {
    if (positive) {
        printf("\033[42mSUCCESSO\033[m\n\n");
    }
    else {
        printf("\033[41mFALLIMENTO\033[m\n\n");
    }
}