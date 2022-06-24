#include "CommonViewHeader.h"

void printAllCourses(Class **classArray, int arrayLen) {
    char *headerArray[] = {"Codice", "Livello", "Numero Allievi", "Data Attivazione"} ;
    enum TableFieldType tableField[] = {INT, STRING, INT, DATE} ;
    
    Table *table = createTable(arrayLen, 4, headerArray, tableField) ;
    for(int i = 0 ; i < arrayLen ; i++) {
        Class *classPtr = classArray[i] ;
        setTableElem(table, i, 0, &(classPtr->classCode)) ;
        setTableElem(table, i, 1, classPtr->levelName) ;
        setTableElem(table, i, 2, &(classPtr->studentsNumber)) ;
        setTableElem(table, i, 3, &(classPtr->activationDate)) ;
    }
    
    printTable(table) ;
    freeTable(table) ;
}