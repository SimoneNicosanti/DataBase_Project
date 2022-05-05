#include "TimeUtils.h"
#include "IOUtils.h"

regex_t dateRegex ;
regex_t timeRegex ;


int daysInMonth[13][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ,
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
} ;


bool compileTimeRegex() {
    if (regcomp(&dateRegex, "[0-9]{4}-[0-9]{2}-[0-9]{2}", REG_EXTENDED) != 0) {
        printError("Impossibile Inizializzare Regex di Controllo Data") ;
        return false ;
    }
    if (regcomp(&timeRegex, "[0-9]{2}:[0-9]{2}", REG_EXTENDED) != 0) {
        printError("Impossibile Inizializzare Regex di Controllo Orario") ;
        return false ;
    }
    return true ;
}

int isLeapYear(int year) {
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}


bool isValidDate(Date *verifyDate) {
    //check range of year,month and day
    //TODO Verificare che sia SQL a fare questo controllo
    if (verifyDate->month < 1 || verifyDate->month > 12) {
        return false ;
    }

    if (verifyDate->day < 1 || verifyDate->day > 31) {
        return false ;
    }

    if (verifyDate->day > daysInMonth[isLeapYear(verifyDate->year)][verifyDate->month]) {
        return false ;
    }

    return true ;
}



bool verifyAndParseDate(Date *datePtr, char *dateString) {

    if (regexec(&dateRegex, dateString, 0, NULL, 0) != 0) {
        return false ;
    }

    char *yearString = strtok(dateString, "-") ;
    char *monthString = strtok(NULL, "-") ;
    char *dayString = strtok(NULL, "-") ;

    if (strlen(yearString) == 4 && strlen(monthString) == 2 && strlen(dayString) == 2) {
        datePtr->year = atoi(yearString) ;
        datePtr->month = atoi(monthString) ;
        datePtr->day = atoi(dayString) ;
        
        //Verifica su Correttezza rapporto tra mese-giorno e anno è fatta dal DBMS
        //return isValidDate(datePtr) ;
        return true ;
    }

    return false ;
}

bool verifyAndParseTime(Time *timePtr, char *timeStr) {
    if (regexec(&timeRegex, timeStr, 0, NULL, 0) != 0) {
        return false ;
    }

    char *hourString = strtok(timeStr, ":") ;
    char *minuteString = strtok(NULL, ":") ;

    if (strlen(hourString) == 2 && strlen(minuteString) == 2) {
        timePtr->hour = atoi(hourString) ;
        timePtr->minute = atoi(minuteString) ;
        return true ;
    }

    return false ;
}