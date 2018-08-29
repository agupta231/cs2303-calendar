#include <stdio.h>
#include <stdlib.h>

#define JAN 0
#define FEB 1
#define MAR 2
#define APR 3
#define MAY 4
#define JUN 5
#define JUL 6
#define AUG 7
#define SEP 8
#define OCT 9
#define NOV 10
#define DEC 11

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

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

int determineFirstDay(int year) {


	int decade = year % 100;	

	return 0;
}

int main(void) {
	int year = getDesiredYear();
	determineFirstDay(year);
}
