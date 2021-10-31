/****************
* Avraham sikirov
* 318731478
* 01
* ex5
***************/

#include "ex5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
	char classId[CLASSID];
	char className[CLASSNAME];

}class;

class allClasses[CLASSID];

struct student
{
	char classId[CLASSID];
	char studentName[STUDENTNAME];
	int grade;
	student_s* next;
};

int isClassNameLegal(char *firstToken, char *secondToken, char temp1[]);
char* deleteSpaces(char* string);
int isCourseExists(char* token);
int isAlphabetic(char* string);
student_s* CreateStudent(char* classId, char* nameOfStudent, int studentGrade);
student_s* findStudent(student_s* headlist, char* classId, char* nameOfStudent);
void printStudent(student_s* headlist);
int isStundetRegLegal(char* string);
int isClassValid(char* string);
int isDeleteStudentLegal(student_s* headlist, char* string);
int IsclassHasStundents(student_s* headlist, char* classId);
void courseAverage(student_s** headlist, int CurrentNumClasses);
void courseMin(student_s** headlist, int CurrentNumClasses);
void courseMax(student_s** headlist, int CurrentNumClasses);
void courseCount(student_s** headlist, int CurrentNumClasses);
void courseSum(student_s** headlist, int CurrentNumClasses);
void freeStudentList(student_s* headlist);

/******************
* Function Name: printMenu
* Input: none
* Output: Print the manu
* Function Operation: Just prints the menu
******************/

void printMenu()
{
	printf("Please select an operation:\n");
	printf("\t0. Exit.\n");
	printf("\t1. Insert or update a class.\n");
	printf("\t2. Insert or update a student.\n");
	printf("\t3. Remove a student from classes.\n");
	printf("\t4. Print a class.\n");
	printf("\t5. Print all classes with their computed scores.\n");
	printf("\t6. Print the menu.\n");
	return;
}

/******************
* Function Name: printSubMenu
* Input: none
* Output: Print the sub manu
* Function Operation: Just prints the sub menu
******************/

void printSubMenu()
{
	printf("Please select the aggregation method:\n");
	printf("\ta. Average Grade.\n");
	printf("\tb. Maximal Grade.\n");
	printf("\tc. Minimal Grade.\n");
	printf("\td. Sum.\n");
	printf("\te. Count.\n");
	printf("\t0. Return to the main menu.\n");
	return;
}

/******************
* Function Name: classAbsorption
* Input: number of maximum classes, and the number of classes exists 
* at the time the functions if called.
* Output: none
* Function Operation: The function scans from the user the input, and the cut it with strtok.
* The function uses an auxiliary function to check the input legality.
* The function checks if there are to much classes at the time and prints the message. 
* if everything is fine, the function assign the new class to the appropriate struct. 
******************/

void classAbsorption(int size, int* CurrentNumClasses)
{
	char temp[ClASSSTRING];
	char temp1[ClASSSTRING];
 	scanf(" %[^\n]", temp);

	char *firstToken = strtok(temp, " ");
	char *secondToken = strtok(NULL, "");
	if (isClassNameLegal(firstToken, secondToken, temp1) == FALSE)
	{
		printf("Error: invalid class number or name.\n");
		return;
	}
	for (int i = 0; i < NUMOFCLASSES; ++i)
	{
		if (strcmp(allClasses[i].classId, firstToken) == 0)
		{
			strcpy(allClasses[i].className, temp1);
			printf("Class \"%s %s\" updated.\n", allClasses[i].classId,
			allClasses[i].className);
			return;
		}
	}
	if (*CurrentNumClasses < NUMOFCLASSES)
	{
		strcpy(allClasses[*CurrentNumClasses].classId, firstToken);
		strcpy(allClasses[*CurrentNumClasses].className, temp1);
		printf("Class \"%s %s\" added.\n", allClasses[*CurrentNumClasses].classId,
			allClasses[*CurrentNumClasses].className);
		++(*CurrentNumClasses);
		return;
	}
	else
	{
		printf("Unfortunately, there is no room for more classes.\n");
		return;
	}
}

/******************
* Function Name: isClassNameLegal
* Input: First and the second piece from the input from the function "classAbsorption"
* and in addition an empty string. 
* at the time the functions if called.
* Output: 0 or 1
* Function Operation: The functions checks if the second part in none, and then return false.
* Then, the function copies the second part of the string to the empty string witout spaces. 
* Then, the function checks the length of the first and the second part and return 0 if the length
* are not correct.
* At the end, the function checks If the first part contains only numbers, 
* and the second part contains letters, and spaces
* If all the checks passed the function return 1 (TRUE)
******************/

int isClassNameLegal(char* firstToken, char* secondToken, char temp1[])
{
	if (secondToken == END_STRING)
	{
		return FALSE;
	}
	int flagSpace = FALSE;
	int position = FALSE;
	for (int i = 0; secondToken[i] != END_STRING; ++i)
	{
		if (secondToken[i] == ' ' && flagSpace == FALSE)
		{
			continue;
		}
		flagSpace = TRUE;
		temp1[position] = secondToken[i];
		++position;
	}
	temp1[position] = END_STRING;
	flagSpace = FALSE;
	for (int i = 0; temp1[i]; ++i)
	{
		if (temp1[i] != SPACE)
		{
			flagSpace = TRUE;
			break;
		}
	}
	if (strlen(firstToken) != CLASSIDLENGTH || strlen(temp1) > CLASSNAMELENGTH || flagSpace == FALSE)
	{
		return FALSE;
	}
	for (int i = 0; firstToken[i] != END_STRING; ++i)
	{
		if (firstToken[i] < MINDEC || firstToken[i] > MAXDEC)
			return FALSE;
	}
	for (int i = 0; secondToken[i] != END_STRING; ++i)
	{
		if (secondToken[i] > BIGLOWCASE || secondToken[i] < SMALLLOWCASE && secondToken[i] > BIGUPPERCASE ||
			secondToken[i] < SMALLUPPERCASE && secondToken[i] > MAXDEC ||
			secondToken[i] < MINDEC && secondToken[i] != SPACE)
		{
			return FALSE;
		}
	}
	return TRUE;
}

/******************
* Function Name: isCourseExists
* Input: pointer to string (name of class).
* Output: Class position is the struct or -1 if the class isn't found.
* Function Operation: The function compares the name of classes exist to the name of the class
* the function got. if the class exists, the function will return it's number. (of the array it belongs to)
* if the class doesn't exists, the function will return -1 (FALSE)
******************/

int isCourseExists(char* token)
{
	for (int i = 0; i < NUMOFCLASSES; ++i)
	{
		if (strcmp(allClasses[i].classId, token) == 0)
		{
			return i;
		}
	}
	return NOTFOUND;
}

/******************
* Function Name: studentRegistration
* Input: pointer to the head of the linklist and a pointer to temp linklist.
* Output: none. (the function adds a student to the linked list.
* Function Operation: The function scans from the user the input,
* The function uses an auxiliary function ("isStundetRegLegal") to check the input legality.
* Then the function cut the first and the second part with strtok and sends the 
* class name to the function checks if the class exists.
* The function also uses auxiliary function to delete all spaces before every token.
* The function also uses auxiliary function to check if student already exists, and then update it's data.
* If the student doesn't exists, and the tokens pass all legality tests, the function uses auxiliary function
* to create new node in the linked list and then connects the node the the linked list. 
******************/

void studentRegistration(student_s** headlist, student_s* templist)
{
	char temp[ClASSSTRING];
	scanf(" %[^\n]", temp);
	if (isStundetRegLegal(temp) == FALSE)
	{
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	char* firstToken = strtok(temp, ":");
	char *secondToken = strtok(NULL, ",");
	while (secondToken != NULL)
	{
		secondToken = deleteSpaces(secondToken);
		if (secondToken == NULL)
			continue;
		char tempSecondToken[CLASSID];
		int i = isCourseExists(secondToken);
		if (i != NOTFOUND)
		{
			strcpy(tempSecondToken, secondToken);
		}
		secondToken = strtok(NULL, ";");
		secondToken = deleteSpaces(secondToken);
		if ((atoi(secondToken)) <= 100 && (atoi(secondToken)) >= 0)
		{
			if (findStudent(*headlist, tempSecondToken, firstToken) == NULL)
			{
				printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n", firstToken,
					tempSecondToken, allClasses[i].className, atoi(secondToken));
				templist = CreateStudent(tempSecondToken, firstToken, atoi(secondToken));
				if (templist == NULL)
				{
					freeStudentList(*headlist);
					exit(1);
				}
				templist->next = *headlist;
				*headlist = templist;
			}
			else
			{
				printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n", firstToken,
					tempSecondToken, allClasses[i].className, atoi(secondToken));
				findStudent(*headlist, tempSecondToken, firstToken)->grade = atoi(secondToken);
			}
		}
		else
		{
			printf("Error: invalid name, class number or grade.\n"); return;
		}
		secondToken = strtok(NULL, ",");
	}
}

/******************
* Function Name: isStundetRegLegal
* Input: pointer to string (from the function studentRegistration)
* Output: 0 or 1
* Function Operation: The function checks the existence of a comma, a semicolon,
* in the right places and an exact number of presence. In addition the function
* checks a sequence of separating characters one after the other
* The function uses strtok to cut and check the right places and uses the auxility
* auxiliary function that deletes spaces before every token. 
******************/

int isStundetRegLegal(char* string)
{
	int countTwoPoints = 0, countComma = 0, countPointComma = 0, countpoint = 0;
	char temp[ClASSSTRING];
	strcpy(temp, string);
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] == ':')
			++countTwoPoints;
		if (string[i] == '.')
			++countpoint;
		if (string[i] == ',')
			++countComma;
		if (string[i] == ';')
			++countPointComma;
		if ((string[i] == ';' || string[i] == ':' || string[i] == ',') && string[i] == string[i + ONE])
		{
			return FALSE;
		}
	}
	if (countPointComma != countComma || countPointComma < ONE || countpoint != 0)
	{
		return FALSE;
	}

	if (countTwoPoints != ONE)
	{
		return FALSE;
	}
	char* firstToken = strtok(temp, ":");
	if (isAlphabetic(firstToken) == FALSE)
	{
		return FALSE;
    }
	char* secondToken = strtok(NULL, ",");
	while (secondToken != NULL)
	{
		secondToken = deleteSpaces(secondToken);
		if (secondToken == NULL)
			continue;
		char tempSecondToken[CLASSID];
		int i = isCourseExists(secondToken);
		if (i == NOTFOUND)
		{
			return FALSE;
			strcpy(tempSecondToken, secondToken);
		}
		secondToken = strtok(NULL, ";");
		secondToken = deleteSpaces(secondToken);
		secondToken = strtok(NULL, ",");
	}
	return TRUE;
}

/******************
* Function Name: isAlphabetic
* Input: pointer to string 
* Output: 0 or 1
* Function Operation: The punctuation goes through all the characters in the array and checks
* that they are uppercase or lowercase or spaces
******************/

int isAlphabetic(char* string)
{
	if (strlen(string) > 20)
	{
		return FALSE;
	}
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] > BIGLOWCASE || string[i] < SMALLLOWCASE && string[i] > BIGUPPERCASE ||
			string[i] < SMALLUPPERCASE && string[i] != SPACE)
		{
			return FALSE;
		}
	}
	return TRUE;
}

/******************
* Function Name: CreateStudent
* Input: pointer to string of classID, stundent name and stundent grade.
* Output: null or pointer to the new node of the list.
* Function Operation: The function uses malloc to assign new place in memory (new struct). 
* then assign the values ​​it received from the function "studentRegistration" and then 
* assign the values to the new struct and the return the pointer to it's location. 
******************/

student_s* CreateStudent(char* classId, char* nameOfStudent, int studentGrade)
{
	student_s* newStudent = (student_s*)malloc(sizeof(student_s));
	
	if (newStudent == NULL)
	{
		return NULL;
	}
	strcpy(newStudent->classId, classId);
	strcpy(newStudent->studentName, nameOfStudent);
	newStudent->grade = studentGrade;
	newStudent->next = NULL;
	return newStudent;
}

/******************
* Function Name: findStudent
* Input: pointer to the head of the linked list. pointer to string of classID and stundent name.
* Output: pointer to the location of the student found or null if not found. 
* Function Operation: The function goes through all the linked list with a loop, the return
* the pointer to the location of the student found or null if not found. 
******************/

student_s* findStudent(student_s* headlist, char* classId, char* nameOfStudent)
{
	student_s* temp = headlist;
	while (temp != NULL)
	{
		if (strcmp(temp->classId, classId) == 0 && strcmp(temp->studentName, nameOfStudent) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/******************
* Function Name: isStudentexists
* Input: pointer to the head of the linked list. pointer stundent name.
* Output: pointer to the location of the student found or null if not found.
* Function Operation: The function goes through all the linked list with a loop, the return
* the pointer to the location of the student found or null if not found.
******************/

student_s* isStudentexists(student_s* headlist, char* nameOfStudent)
{
	student_s* temp = headlist;
	while (temp != NULL)
	{
		if (strcmp(temp->studentName, nameOfStudent) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/******************
* Function Name: findBeforeStudent
* Input: pointer to the head of the linked list. pointer to string of classID and stundent name.
* Output: pointer to the location of the student before if found or null if not found.
* Function Operation: The function goes through all the linked list with a loop, the return
* the pointer to the location of the student before if found or null if not found.
******************/

student_s* findBeforeStudent(student_s* headlist, char* classId, char* nameOfStudent)
{
	student_s* temp = headlist;
	
	while (temp != NULL)
	{
		
		if (strcmp(temp->next->classId, classId) == 0 && strcmp(temp->next->studentName, nameOfStudent) == 0)
		{
			
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/******************
* Function Name: printStudent
* Input: pointer to the head of the linked list. 
* Output: prints the student with it's values.
* Function Operation: The function goes through all the linked list with a loop, 
* and prints all the student in it with their values. 
******************/

void printStudent(student_s* headlist)
{
	student_s* current = headlist;

	while (current != NULL)
	{
		printf("class: %s\n", current->classId);
		printf("name: %s\n", current->studentName);
		printf("grade: %d\n", current->grade);
		current = current->next;
	}

}

/******************
* Function Name: deleteSpaces
* Input: pointer to string
* Output: pointer to string 
* Function Operation: The function goes over the array and deletes all
* spaces that precede the first character that is not a space. 
* If there is an initial space the function promotes the pointer
******************/

char* deleteSpaces(char* string)
{
	int flag = FALSE;
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] != SPACE)
			flag = TRUE;
	}
	if (flag == FALSE)
		return NULL;
	while (*string == ' ' && *string != NULL)
	{
		string++;
	}

	return string;
}

/******************
* Function Name: deleteStudent
* Input: pointer to the head of the linked list.
* Output: pointer to string
* Function Operation: The function scans from the user the input,
* The function uses an auxiliary function ("isDeleteStudentLegal") to check the input legality.
* Then the function cut the first and the second part with strtok. 
* The function uses an auxiliary function to check if the course you want to delete from is exists. 
* In addition, the function checks if there are other courses for which the student is registered
*Finally if all the correctness has passed, the function deletes the student by having the student
* in front of him on the linked list point to the one after him. and then freeing the memory. 
******************/

void deleteStudent(student_s** headlist)
{
	char temp[ClASSSTRING];
	scanf(" %[^\n]", temp);
	int check = isDeleteStudentLegal(*headlist, temp);
	if (check == ERROR_TYPE1)
	{
		printf("Error: invalid name or class number.\n"); 
		return;
	}
	if (check == ERROR_TYPE2)
	{
		 return;
	}
	char* firstToken = strtok(temp, ":");
	char* secondToken = strtok(NULL, ",");
	while (secondToken != NULL)
	{
		secondToken = deleteSpaces(secondToken);
		int i = isCourseExists(secondToken);
		student_s* ifHead = *headlist;
		if (strcmp(ifHead->classId, secondToken) == 0 && strcmp(ifHead->studentName, firstToken) == 0)
		{
			*headlist = ifHead->next; 
			free(ifHead);
		}
		else
		{
			student_s* deleteS = findBeforeStudent(*headlist, secondToken, firstToken);
			student_s* deleteS1 = deleteS->next;
			deleteS->next = deleteS->next->next; 
			free(deleteS1);
		}
		printf("Student \"%s\" removed from class \"%s %s\".\n", firstToken, secondToken, allClasses[i].className);
		secondToken = strtok(NULL, ",");
	}
}

/******************
* Function Name: isDeleteStudentLegal
* Input: pointer to string (from the function deleteStudent)
* Output: 0 or 1
* Function Operation: The function checks the existence of a comma and a colon,
* in the right places and an exact number of presence. In addition the function
* checks a sequence of separating characters one after the other
* The function uses strtok to cut and check the right places and uses the auxility
* auxiliary function that deletes spaces before every token.
******************/

int isDeleteStudentLegal(student_s* headlist, char* string)
{
	int countTwoPoints = FALSE, countcomma = FALSE, numberOfLoops = FALSE;
	char temp[ClASSSTRING];
	strcpy(temp, string);
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] == ':')
			++countTwoPoints;
		if (string[i] == ',')
			++countcomma;
		if ((string[i] == ',') && string[i] == string[i + ONE])
		{
			return ERROR_TYPE1;
		}
	}
	if (countTwoPoints != ONE || countcomma < ONE)
	{
		return ERROR_TYPE1;
	}
	char* firstToken = strtok(temp, ":");
	if (isAlphabetic(firstToken) == FALSE)
	{
		return ERROR_TYPE1;
	}
	char* secondToken = strtok(NULL, ",");
	while (secondToken != NULL)
	{
		secondToken = deleteSpaces(secondToken);
		int i = isCourseExists(secondToken);
		if (i == NOTFOUND || isStudentexists(headlist, firstToken) == NULL)
		{
			 return ERROR_TYPE1;
		}
		if (findStudent(headlist, secondToken, firstToken) == NULL)
		{
			printf("Error: student is not a member of class \"%s %s\".\n", secondToken, allClasses[i].className);
			return ERROR_TYPE2;
		}
		student_s* current = headlist;
		int howManyClasses = FALSE;
		while (current != NULL)
		{
			if (strcmp(current->studentName, firstToken) == 0)
				++howManyClasses;
			current = current->next;
		}
		if (howManyClasses - numberOfLoops <= TRUE)
		{
			printf("Error: student cannot be removed from all classes.\n");
			return ERROR_TYPE2;
		}
		++numberOfLoops;
		secondToken = strtok(NULL, ",");
	}
	return TRUE;
}

/******************
* Function Name: printClassWithStudents
* Input: pointer to the head of the linked list.
* Output: 0 or 1
* Function Operation: The function scans from the user the input,
* The function uses an auxiliary function ("isClassValid") to check the input legality. and the function 
* "isCourseExists" to check if the course exists. 
* Then the function goes over the linked list, compare the name of the stundent
* and the class to count how many students in this class.
* If the validity test has passed, the function puts all students in the course into an array.
* Then uses buble sort algorithm to sort the students by letter and finally prints them in that order.
******************/

void printClassWithStudents(student_s** headlist)
{
	int studentCount = FALSE, flag = FALSE;
	char temp[ClASSSTRING];
	scanf(" %[^\n]", temp);
	if (isClassValid(temp) == FALSE)
	{
		printf("Error: invalid class number.\n"); return;
	}
	int numberOfCourse = isCourseExists(temp);
	flag = IsclassHasStundents(*headlist, temp);
	if (flag != FALSE)
	{
		printf("Class \"%s %s\" students:\n", temp, allClasses[numberOfCourse].className); 
		student_s* studentArray = (student_s*)calloc(flag, sizeof(student_s));
		if (studentArray == NULL)
		{
			freeStudentList(*headlist); exit(1);
		}
		student_s* current = *headlist;
		for (int i = 0; current != NULL;)
		{
			if (strcmp(current->classId, temp) == FALSE)
			{
				strcpy(studentArray[i].studentName, current->studentName);
				studentArray[i].grade = current->grade;
				++i;
			}
			current = current->next;
		}
		for (int i = 0; i < flag; ++i)
		{
			for (int j = i + 1; j < flag; ++j)
			{
				if (strcmp(studentArray[i].studentName, studentArray[j].studentName) > 0)
				{
					student_s* temp1 =(student_s *)malloc(sizeof(student_s));
					if (temp1 == NULL)
					{
						freeStudentList(*headlist); free(studentArray);
						exit(1);
						
					}
					strcpy(temp1->studentName, studentArray[i].studentName);
					temp1->grade = studentArray[i].grade;
					strcpy(studentArray[i].studentName, studentArray[j].studentName);
					studentArray[i].grade = studentArray[j].grade;
					strcpy(studentArray[j].studentName, temp1->studentName);
					studentArray[j].grade = temp1->grade;
					free(temp1);
				}
			}
		}
		for (int i = 0; i < flag; ++i)
		{
			printf("%s, %d\n", studentArray[i].studentName, studentArray[i].grade);
		}
		free(studentArray);
		return;
	}
	printf("Class \"%s %s\" has no students.\n", temp, allClasses[numberOfCourse].className); return;
	
}

/******************
* Function Name: isDeleteStudentLegal
* Input: pointer to the head of the linked list and pointer to classid string. 
* Output: 0 or 1
* Function Operation: The function goes through the whole list and compares it the the classid.
* in addition counts the number of student the class and then return the number of them, of 0 is there no one.
******************/

int IsclassHasStundents(student_s* headlist, char* classId)
{
	int flag = FALSE;
	int count = FALSE;
	student_s* current = headlist;
	while (current != NULL)
	{
		if (strcmp(current->classId, classId) == FALSE)
		{
			flag = TRUE;
			++count;

		}
		current = current->next;
	}

	if (flag == TRUE)
		return count;
	else
		return FALSE;
}

/******************
* Function Name: isClassValid
* Input: pointer string
* Output: 0 or 1
* Function Operation: The function cheks string length and that it consist of only digits.
* and uses the function "isCourseExists" to check if the course exists.
******************/

int isClassValid(char* string)
{
	if (strlen(string) != NUMOFCLASSES)
	{
		return FALSE;
	}
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] < MINDEC || string[i] > MAXDEC)
		{
			return FALSE;
		}
	}
	if (isCourseExists(string) == NOTFOUND)
	{
		return FALSE;
	}

	return TRUE;
}

/******************
* Function Name: printAllClasses
* Input: head of the link list and amount to classes exists. 
* Output: prints sub menu. 
* Function Operation: The function waits for the input and calls the function
* corresponding to the action according to the input
******************/

void printAllClasses(student_s** headlist, int CurrentNumClasses)
{
	if (CurrentNumClasses == FALSE)
	{ 
		printf("Error: there are no classes.\n");
		return;
	}
	printSubMenu();
	char choise;
	int avrage;
	int countdevide;
	scanf(" %c", &choise);
	if (choise == 'a')
	{
		courseAverage(headlist, CurrentNumClasses);
	}
	else if (choise == 'b')
	{
		courseMax(headlist, CurrentNumClasses);
	}
	else if (choise == 'c')
	{
		courseMin(headlist, CurrentNumClasses);
	}
	else if (choise == 'd')
	{
		courseSum(headlist, CurrentNumClasses);
	}
	else if (choise == 'e')
	{
		courseCount(headlist, CurrentNumClasses);
	}
	else
		return;
}

/******************
* Function Name: courseAverage
* Input: pointer to the head of the link list and amount to classes exists.
* Output: prints the average of grades.
* Function Operation: The function goes through the entire list and performs an average
* calculation of the students relevant to the same course and the prints the average. 
* And so in a loop for all courses
******************/

void courseAverage(student_s** headlist , int CurrentNumClasses)
{
	int average = FALSE;
	int count = FALSE;
	for (int i = 0; i < CurrentNumClasses; ++i)
	{
		if (IsclassHasStundents(*headlist, allClasses[i].classId) == FALSE)
		{
			printf("Class \"%s %s\" has no students.\n", allClasses[i].classId, allClasses[i].className);
			continue;
		}
		student_s* current = *headlist;
		while (current != NULL)
		{
			if (strcmp(current->classId, allClasses[i].classId) == 0)
			{
				average = average + current->grade;
				++count;
			}
			current = current->next;
		}
		printf("%s %s, %d\n", allClasses[i].classId, allClasses[i].className, (average / count));
		average = FALSE;
		count = FALSE;
	}
	return;
}

/******************
* Function Name: courseMin
* Input: pointer to the head of the link list and amount to classes exists.
* Output: prints the minimal grade.
* Function Operation: The function goes through the entire list and check the minimal grade
* of the students relevant to the same course and the prints the minimal grade.
* And so in a loop for all courses
******************/

void courseMin(student_s** headlist, int CurrentNumClasses)
{
	int min = FALSE;
	int temp = MAXGRADE;
	for (int i = 0; i < CurrentNumClasses; ++i)
	{
		if (IsclassHasStundents(*headlist, allClasses[i].classId) == FALSE)
		{
			printf("Class \"%s %s\" has no students.\n", allClasses[i].classId, allClasses[i].className);
			continue;
		}
		student_s* current = *headlist;
		while (current != NULL)
		{
			if (strcmp(current->classId, allClasses[i].classId) == 0)
			{
				if (current->grade < temp)
				{
					
					min = current->grade;
					temp = min;
				}
			}
			current = current->next;
		}
		printf("%s %s, %d\n", allClasses[i].classId, allClasses[i].className, min);
		min = FALSE;
		temp = MAXGRADE;
	}
	return;
}

/******************
* Function Name: courseMax
* Input: pointer to the head of the link list and amount to classes exists.
* Output: prints the minimal grade.
* Function Operation: The function goes through the entire list and check the max grade
* of the students relevant to the same course and the prints the max grade.
* And so in a loop for all courses
******************/

void courseMax(student_s** headlist, int CurrentNumClasses)
{
	int max = FALSE;
	int temp = FALSE;
	for (int i = 0; i < CurrentNumClasses; ++i)
	{
		if (IsclassHasStundents(*headlist, allClasses[i].classId) == FALSE)
		{
			printf("Class \"%s %s\" has no students.\n", allClasses[i].classId, allClasses[i].className);
			continue;
		}
		student_s* current = *headlist;
		while (current != NULL)
		{
			if (strcmp(current->classId, allClasses[i].classId) == 0)
			{
				if (current->grade > temp)
				{

					max = current->grade;
					temp = max;
				}
			}
			current = current->next;
		}
		printf("%s %s, %d\n", allClasses[i].classId, allClasses[i].className, max);
		max = FALSE;
		temp = FALSE;
	}

	return;
}

/******************
* Function Name: courseSum
* Input: pointer to the head of the link list and amount to classes exists.
* Output: prints the minimal grade.
* Function Operation: The function goes through the entire list and calculate the sum of the graded
* of the students relevant to the same course and the prints the sum.
* And so in a loop for all courses
******************/

void courseSum(student_s** headlist, int CurrentNumClasses)
{
	int sum = FALSE;
	for (int i = 0; i < CurrentNumClasses; ++i)
	{
		if (IsclassHasStundents(*headlist, allClasses[i].classId) == FALSE)
		{
			printf("Class \"%s %s\" has no students.\n", allClasses[i].classId, allClasses[i].className);
			continue;
		}
		student_s* current = *headlist;
		while (current != NULL)
		{
			if (strcmp(current->classId, allClasses[i].classId) == 0)
			{
				sum = sum + (*current).grade;
			}
			current = current->next;
		}
		printf("%s %s, %d\n", allClasses[i].classId, allClasses[i].className, sum);
		sum = FALSE;
	}
	return;
}

/******************
* Function Name: courseCount
* Input: pointer to the head of the link list and amount to classes exists.
* Output: prints the minimal grade.
* Function Operation: The function goes through the entire list and calculate the number of students
* of the students relevant to the same course and the prints the amount.
* And so in a loop for all courses
******************/

void courseCount(student_s** headlist, int CurrentNumClasses)
{
	int count = FALSE;
	for (int i = 0; i < CurrentNumClasses; ++i)
	{
		if (IsclassHasStundents(*headlist, allClasses[i].classId) == FALSE)
		{
			printf("Class \"%s %s\" has no students.\n", allClasses[i].classId, allClasses[i].className);
			continue;
		}
		student_s* current = *headlist;
		while (current != NULL)
		{
			if (strcmp(current->classId, allClasses[i].classId) == 0)
			{
				++count;
			}
			current = current->next;
		}
		printf("%s %s, %d\n", allClasses[i].classId, allClasses[i].className, count);
		count = FALSE;
	}
	return;
}

/******************
* Function Name: freeStudentList
* Input: pointer to the head of the link list 
* Output: none
* Function Operation: The function goes through the entire list and freeing every node in it.
******************/

void freeStudentList(student_s* headlist)
{
	student_s* temp;

	while (headlist != NULL)
	{
		temp = headlist;
		headlist = headlist->next;
		free(temp);
	}

}