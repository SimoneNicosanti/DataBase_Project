#pragma once

#include "Class.h"
#include "Teacher.h"
#include "Student.h"
#include "../utils/TimeUtils.h"


enum DayOfWeek {
    MONDAY = 0 ,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} ;


typedef struct {
    enum DayOfWeek dayOfWeek ;
    Time startTime ;
    int classCode ;
    char classLevel[LEVEL_NAME_MAX_LEN + 1] ;
    int lessonDuration ;
    char teacherName[TEACHER_NAME_MAX_LENGHT + 1] ;
} ClassLesson ;


typedef struct {
    Date lessonDate ;
    Time startTime ;
    int lessonDurability ;
    char lessonTeacher[TEACHER_NAME_MAX_LENGHT + 1] ;
    char lessonStudent[STUDENT_NAME_MAX_LEN + 1] ;
} PrivateLesson ;


typedef struct {
    Date lessonDate ;
    Time startTime ;
    int lessonDuration ;
    int lessonType ;
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char studentName[STUDENT_NAME_MAX_LEN] ;
} GeneralLesson ;