#include <stdio.h>
#include <stdlib.h>

int getDesiredYear() {
	int userYear;

	printf("Please enter the year for this calendar: ");
	scanf("%d", &userYear);

	if(userYear < 1583) {
		printf("You inputted an invalid year. Please input a year >= 1583");
		exit(1);
	}

	return userYear;
}

int main(void) {
	int year = getDesiredYear();
}
