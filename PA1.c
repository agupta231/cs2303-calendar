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

#define SUN 1
#define MON 2
#define TUE 3
#define WED 4
#define THU 5
#define FRI 6
#define SAT 0

int getDesiredYear(void) {
	int userYear;

	printf("Please enter the year for this calendar: ");
	scanf("%d", &userYear);

	if(userYear < 1583) {
		printf("Invalid year. Please input a year >= 1583");
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
			return 2;
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

int yearAdjustment(int year) {
	int century = year / 100;
	
	while(!(century >= 17 && century <= 20)) {
		century -= 4;
	}

	switch(century) {
		case 17:
			return 4;
		case 18:
			return 2;
		case 19:
			return 0;
		case 20:
			return 6;
		default:
			printf("Invalid century %d", century);
			return -1;
	}
}

int isLeapYear(int year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int determineFirstDay(int month, int year) {
	int decade = year % 100;
	int monthAdjusted = decade / 4 + monthKey(JAN) + 1;

	if((month == JAN || month == FEB) && isLeapYear(year)) {
		monthAdjusted -= 1;
	}

	int centuryAdjusted = monthAdjusted + \
		yearAdjustment(year) + decade;

	return centuryAdjusted % 7;
}

int main(void) {
	int year = getDesiredYear();

	if(year == -1) {
		return 1;
	}

	printf("%d\n", determineFirstDay(JAN, year));
}
