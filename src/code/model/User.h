#pragma once


#define USERNAME_MAX_SIZE 45
#define PASSWORD_MAX_SIZE 45

//Take one more char for \0
typedef struct {
    char username[USERNAME_MAX_SIZE + 1] ;
    char password[PASSWORD_MAX_SIZE + 1] ;
} User ;

typedef enum {
    AMMINISTRAZIONE = 0,
    SEGRETERIA,
    INSEGNANTE,
    LOGIN
} Role ;