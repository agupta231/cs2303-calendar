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

int getDesiredYear(void) {
	int userYear;

	printf("Please enter the year for this calendar: ");
	scanf("%d", &userYear);

	if(userYear < 1583) {
		printf("You inputted an invalid year. Please input a year >= 1583");
		return -1;
	}

	return userYear;
}

int monthKey(int month) {
	switch(month) {
		case JAN:
			return 1;
		case FEB:
			return 4;
		case MAR:
			return 4;
		case APR:
			return 0;
		case MAY:
			return 2:
		case JUN:
			return 5;
		case JUL:
			return 0;
		case AUG:
			return 3;
		case SEP:
			return 6;
		case OCT:
			return 1;
		case NOV:
			return 4;
		case DEC:
			return 6;
		default:
			printf("Invalid month inputted to monthKey");
			return -1;
	}
}

int determineFirstDay(int month, int year) {
	static int dayOfMonth = 1;

	int decade = year % 100;
	int monthAdjusted = decade / 4 + monthKey(JAN);
}

int main(void) {
	int year = getDesiredYear();

	if(year == -1) {
		return 1;
	}

	determineFirstDay(year);
}
