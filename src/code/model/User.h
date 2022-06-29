#pragma once


#define USERNAME_MAX_SIZE 45 + 1
#define PASSWORD_MAX_SIZE 45 + 1

//Take one more char for \0
typedef struct {
    char username[USERNAME_MAX_SIZE] ;
    char password[PASSWORD_MAX_SIZE] ;
} User ;

typedef enum {
    AMMINISTRAZIONE = 0,
    SEGRETERIA,
    INSEGNANTE,
    LOGIN
} Role ;