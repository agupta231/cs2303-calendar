/* 
 * Program to print out the calendar for any year.
 *
 * Author: Ankur Gupta
 * Email: agupta4@wpi.edu
 * 
 * A good chunk of this code is translated math from 
 * http://mathforum.org/dr.math/faq/faq.calendar.html, which states a formula to
 * get the day of week for any date in time. This formula is used to determine
 * the first day of week in a month, and then the calendar is generated from
 * there. 
 *
 * More details about this and why I implemented the things the way I did can be
 * found in the readme.
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

	// Prompt the user for the desired year for the calendar
	printf("Please enter the year for this calendar: ");
	scanf("%d", &userYear);

	// 1583 was the first year of the Gregorian calendar, thus all dates before
	// that are invalid. If the date is invalid, send back a -1 as a flag
	// indicating the main program to exit.
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
	// Return the corresponding month key for a given month. These keys correlate
	// to the math requried to find out the day of week for any date in any year.
	// These values can be found online.
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
			// Somehow a non-month integer gets passed through, output an error
			// message
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
	// Get the first two digits of the year. Because of how integer division works
	// in C, dividing by 100 will truncate the number at the decimal point,
	// essentially flooring the number.
	int century = year / 100;
	
	// The math only works if the first two digits in the year are in the range 
	// [17, 20], and if not, then you have to +/- 4 until you are in the range (as
	// the calendar repeats itself every 400 years)
	
	// If the first two digits are less than 17, then add the respective number of
	// 4's
	if(century < 17) {
		// Do the math to determine how many 4's need to be added, and then multiply
		// by 4 to get the the first two digits of the year into the range. While
		// this expression may look like it can be simplifed to 20 - century, there
		// is actually an implict mathematical flooring going on because these are
		// integer operations.
		century += ((20 - century) / 4) * 4;
	}
	else if(century > 20) {
		// Do the math to determine how many 4's need to be substracted.
		// 
		// The math is the same as the previous conditional block, it's just 
		// subtraction other than multiplication. 
		//
		// One thing to note is that this can also be naively using a loop to 
		// subtract the fours. However, by creating a mathetmatical expression, the
		// runtime of this code block goes from O(n), where n is (year - 17) / 4, to
		// O(1). This makes it so that the time to calculate the calendar for 1600
		// is the same as the time to calculate the calendar for 71823947.
		century -= ((century - 17) / 4) * 4;
	}

	// Return the value for the century. These numbers correlate to the math
	// for the day of week calculation, and can be found on the website.
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
			// Incase there is something funky with the previous calcuations, this 
			// line will spit out an error message.
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
	// Boolean logic to determine if the given year is a leap year or not
	// If the year is divisible by 400, then return true
	// If the year is divislbe by 4 but NOT 100, then return true,
	// else return false
	//
	// Yes, yes, I know that there would be less function calls if I statically
	// stored the year and set a flag just once... but I tried to design it
	// dynamically (be able to print out the calendar for multiple years) and/or
	// was too lazy to make it perfectly optimal because the performace gain is
	// pretty minimal.
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
	// Get the last two digits of the year, as required per the formula
	int decade = year % 100;

	// Apply the month adjustment, as required per the formula. On the website,
	// this line correlates to steps 2 - 4
	int monthAdjusted = decade / 4 + monthKey(month) + 1;

	// If the month is Janurary or Feburary of a leap year, then the formula
	// requires that 1 be subtracted from sum. 
	// This correlates to step 5 on the website.
	if((month == JAN || month == FEB) && isLeapYear(year)) {
		monthAdjusted -= 1;
	}

	// Apply the century adjustment, as required per the formula. This correlates
	// to steps 6 - 7 from the website
	int centuryAdjusted = monthAdjusted + yearAdjustment(year) + decade;

	// As per the formula, take the mod 7 and that will be the day of week, which

	// As per the formula, take the mod 7 and that will be the day of week, which
	// are defined as constants above// are defined as constants above
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
	// Map the weekday constants to a 0-indexed value to make printing easier.
	// In fact, to completely change the look of the calendar, you will just have
	// to modify this function and how the header looks..
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
			// Incase there is some weird case where the day isn't a weekday
			printf("Invalid day given %d", day);
			break;
	}

	// Return a flag indicating that there was an issue with the function.
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

	// The space taken up by a single date + spacing is 5 spaces. In order to
	// fill in the whitespace for empty dates, the loop needs to insert (i * 5)
	// spaces, as the printing standard is 0-indexed.
	//
	// Loop invariant:
	// The left side on the line is either spaces or nothing
	// The cursor is between 0 and 5 * startpos (Which is the number of required
	// whitespace.
	// The right side of the line doesn't have anything.
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
