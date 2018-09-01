/* 
 * Program to print out the calendar for any year.
 *
 * Author: Ankur Gupta
 * Email: agupta4@wpi.edu
 * 
 */
#include <stdio.h>

/*
 * Global constants for enumerating the months of the year. A better solution
 * would have been to use an enum or struct, but we are not supposed to use
 * those for this project.
 */
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

/*
 * Global constants for enumerating the days of the week. Again a better
 * solution would have been to use an enum or struct, but oh well. These numbers
 * are funky becuase they are designed to work with the math in this proejct.
 */
#define SUN 1
#define MON 2
#define TUE 3
#define WED 4
#define THU 5
#define FRI 6
#define SAT 0


/**
 * @brief User input function. 
 *
 * Data cleanses the input and prevents the human from... well, being a human.
 * Because this program is based around the Gregorian calendar, dates only after
 * 1583 work.
 *
 * @return (int) valid year that the human inputted. -1 otherwise.
 */
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

/**
 * @brief Function to return a month's key value.
 * 
 * This function goes hand-with-hand with the math required for this project.
 * The function is basically an array/struct in its functionality, but was
 * implemented this way as per requriements of the project.
 *
 * @param month (int) representation of the desired month, as per the constants
 *							defined before
 *
 * @return (int) the month's key value, to be used in calculations.
 */
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

/**
 * @brief A function that maps a year to its century code.
 *
 * A simple mapping function that maps a year to its century code. Because
 * century codes are only defined for 1700 - 2000, a little bit of math is
 * required to translate any year the be in that range.
 *
 * @param year (int) desired year to get the century code for.
 *
 * @return (int) the century code for the inputted year.
 */
int yearAdjustment(int year) {
	int century = year / 100;

	if(century < 17) {
		century += ((20 - century) / 4) * 4;
	}
	else if(century > 20) {
		century -= ((century - 17) / 4) * 4;
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


/**
 * @brief Determine if a given year is a leap year.
 *
 * A helper function that determines if the inputted year is a leap year or not.
 * Accounts for all of the cases, and is mostly used so that the code stays DRY.
 *
 * @param year (int) year that needs to check if it is a leap year or not
 *
 * @return (boolean) 1 if it is a leap year, 0 otherwise.
 */
int isLeapYear(int year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

/**
 * @brief Determine the first weekday of the month.
 *
 * A function that will determine which day of the week the first day of a given
 * month of a given year will fall on. It should be noted that this function
 * works based off the weekdays constants defined above, which may not
 * correlate to how they are printed out on the screen.
 *
 * @param month (int) month to get the first weekday of 
 * @param year (int) user inputted year
 *
 * @return (int) a day, as defined by the constants above, which represents that
 *							 the first day of the month lands on that day.
 */
int determineFirstDay(int month, int year) {
	int decade = year % 100;
	int monthAdjusted = decade / 4 + monthKey(month) + 1;

	if((month == JAN || month == FEB) && isLeapYear(year)) {
		monthAdjusted -= 1;
	}

	int centuryAdjusted = monthAdjusted + \
		yearAdjustment(year) + decade;

	return centuryAdjusted % 7;
}

/**
 * @brief Convert the weekday to a 0-indexed array position.
 *
 * As the weekday constants may or may not correleate to the order in which they
 * may be printed out, this function maps those constants to a 0-indexed
 * position, which is a lot easier to deal with when printing out the calendar.
 *
 * @param day (int) constant that represents the day of the week
 *
 * @return (int) a 0-indexed position that correlates to the printed position of
 *				 the day
 */
int firstDayToCalendarPosition(int day) {
	switch(day) {
		case SUN:
			return 0;
		case MON:
			return 1;
		case TUE:
			return 2;
		case WED:
			return 3;
		case THU:
			return 4;
		case FRI:
			return 5;
		case SAT:
			return 6;
		default:
			printf("Invalid day given %d", day);
			break;
	}

	return -1;
}

/**
 * @brief Formats and prints out a week.
 *
 * @param startPos (int) the position of the first significant date in the week.
 * @param startNumber (int) the date of the first day of the week.
 * @param month (int) what month the week is int (as per the constants)
 * @param isLeapYear (boolean) if the current year is a leap year;
 */
void printWeek(int startPos, 
							 int startNumber,
							 int month,
							 int isLeapYear) {

	for(int i = 0; i < 5 * startPos; i++) {
		printf(" ");
	}

	int currentDay = startNumber;
	for(int i = startPos; i < 7; i++) {
		if(currentDay < 10) {
			printf("  ");
		} else {
			printf(" ");
		}

		printf("%d", currentDay);

		if(currentDay == 31) {

		}
	}
}

/**
 * @brief Formats and prints out the calendar for a month;
 *
 * @param month (int) month as an int (as per the consants)
 * @param year (int) the year the month is in.
 */
void printMonth(int month, int year) {
	printf("\n\n");

	switch(month) {
		case JAN:
			printf("January %d", year);
			break;
		case FEB:
			printf("Feburary %d", year);
			break;
		case MAR:
			printf("March %d", year);
			break;
		case APR:
			printf("April %d", year);
			break;
		case MAY:
			printf("May %d", year);
			break;
		case JUN:
			printf("June %d", year);
			break;
		case JUL:
			printf("July %d", year);
			break;
		case AUG:
			printf("August %d", year);
			break;
		case SEP:
			printf("September %d", year);
			break;
		case OCT:
			printf("October %d", year);
			break;
		case NOV:
			printf("November %d", year);
			break;
		case DEC:
			printf("December %d", year);
			break;
	}
 
	printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");

	int startPos = firstDayToCalendarPosition(determineFirstDay(month, year));
	int currentDay = 1;

	for(int i = 0; i < 5 * startPos; i++) {
		printf(" ");
	}

	for(int week = 0; week <= 6; week++) {
		for(int day = startPos; day < 7; day++) {
			if(currentDay < 10) {
				printf("  ");
			} else {
				printf(" ");
			}

			printf("%d  ", currentDay);

			if((month == JAN ||
						month == MAR ||
						month == MAY ||
						month == JUL ||
						month == AUG ||
						month == OCT ||
						month == DEC) && 
					currentDay >= 30) {

				if(currentDay == 30) {
					currentDay++;
					continue;
				} else if (currentDay == 31) {
					return;
				}
			} else if (currentDay == 30) {
				return;
			} else if (month == FEB && currentDay >= 28) {
				if(!isLeapYear(year) && currentDay == 28) {
					return;
				} else if(isLeapYear(year) && currentDay == 29) {
					return;
				}
			}

			currentDay++;
		}

		printf("\n");
		startPos = 0;
	}
}

/**
 * @brief Format and print out the calendar for a year
 *
 * @param year (int) year to print out the calendar for
 */
void printCalendar(int year) {
	printf("***    Calendar for %d    ***", year);

	for(int i = 0; i < 12; i++) {
		printMonth(i, year);
		printf("\n");
	}
}

int main(void) {
	printf("***    Monthly Calendar    ***\n");

	int year = getDesiredYear();

	if(year == -1) {
		return 1;
	}

	printCalendar(year);
}
