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
    char classLevel[LEVEL_NAME_MAX_LEN] ;
    int lessonDuration ;
    char teacherName[TEACHER_NAME_MAX_LEN] ;
} ClassLesson ;


typedef struct {
    Date lessonDate ;
    Time startTime ;
    int lessonDurability ;
    char lessonTeacher[TEACHER_NAME_MAX_LEN] ;
    char lessonStudent[STUDENT_NAME_MAX_LEN] ;
} PrivateLesson ;


enum LessonType {
    COURSE = 0 ,
    PRIVATE = 1
} ;

typedef struct {
    Date lessonDate ;
    Time startTime ;
    Time endTime ;
    enum LessonType lessonType ;
    int classCode ;
    char levelName[LEVEL_NAME_MAX_LEN] ;
    char studentName[STUDENT_NAME_MAX_LEN] ;
} GeneralLesson ;

typedef struct {
    Date lessonDate ;
    Time startTime ;
    int duration ;
    enum LessonType lessonType ;
} ReportLesson ;