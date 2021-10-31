/****************
* Avraham sikirov
* 318731478
* 01
* ex5
***************/
#include "ex5.h"
#include <stdio.h>
#include <string.h>


int main()
{
	freopen("C:\\Users\\avrah\\source\\repos\\Ex5\\Ex5\\input.txt", "r", stdin);
	freopen("C:\\Users\\avrah\\source\\repos\\Ex5\\Ex5\\output.txt", "w", stdout);

	student_s* headlist = NULL;
	student_s* templist = NULL;
	int CurrentNumClasses = FALSE;
	char choise = TRUE;
	printMenu();
	while (choise != FALSE)
	{
		scanf(" %c", &choise);
		if (choise == '0')
		{
			freeStudentList(headlist);
			return;
		}
		else if (choise == '1')
		{
			classAbsorption(NUMOFCLASSES, &CurrentNumClasses);
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
		else if (choise == '2')
		{
			studentRegistration(&headlist, templist);
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
		else if (choise == '3')
		{
			deleteStudent(&headlist);
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
		else if (choise == '4')
		{
			printClassWithStudents(&headlist);
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
		else if (choise == '5')
		{
			printAllClasses(&headlist, CurrentNumClasses);
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
		else if (choise == '6')
		{
			printMenu();
		}
		else
		{
			printf("Error: unrecognized operation.\n");
			printf("Select the next operation (insert 6 for the entire menu):\n");
		}
	}
	return 0;
}

