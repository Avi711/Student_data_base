/****************
* Avraham sikirov
* 318731478
* 01
* ex5
***************/
#ifndef heade_h
#define heade_h 



#define _CRT_SECURE_NO_WARNINGS
#define CLASSID 6
#define NUMOFCLASSES 5
#define CLASSIDLENGTH 5
#define CLASSNAMELENGTH 30
#define CLASSNAME 31
#define STUDENTNAME 21
#define ClASSSTRING 201
#define MINDEC 48
#define MAXDEC 57
#define BIGLOWCASE 122
#define SMALLLOWCASE 97
#define BIGUPPERCASE 90
#define SMALLUPPERCASE 65
#define SPACE ' '
#define NOTFOUND -1
#define TRUE 1
#define FALSE 0
#define MAXGRADE 100
#define ONE 1
#define END_STRING '\0'
#define ERROR_TYPE1 2
#define ERROR_TYPE2 3



typedef struct student student_s;

 void printStudent(student_s* headlist);
void printMenu();
void classAbsorption(int size, int* CurrentNumClasses);
void studentRegistration(student_s** headlist, student_s* templist);
void deleteStudent(student_s** headlist);
void printClassWithStudents(student_s** headlist);
void printAllClasses(student_s** headlist, int CurrentNumClasses);
void freeStudentList(student_s* headlist);

#endif 