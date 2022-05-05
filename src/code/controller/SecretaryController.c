#include "SecretaryControllerHeader.h"


void secretaryController() {

    do {
        int selectedOption = getSecretaryOption() ;

        showOptionHeader() ;
        switch (selectedOption) {

            case ADD_STUDENT :
                break; ;

            case QUIT :
                goto exit_loop ;

            default :
                printf("INVALID OPTION\n\n") ;
                break ;
        }
        showOptionHeader() ;
    } while (true) ;

    exit_loop:
    showOptionHeader() ;
}