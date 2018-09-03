# CS2303 Project 1 - Calendar

This is the code base for my first project for CS2303. 

Author: Ankur Gupta

Email: agupta4@wpi.edu

## Summary

This program will calculate and print out a formatted calendar for any valid
year. The validity requirements for any give year is:

* The year must be greater than 1583. This is the year when the Gregorian 
  Calendar was instated, and any year before that is technically incorrect.
* The year is less than the size of an integer. If the year is bigger than the
  size of the integer, than there will be an integer overflow error. However,
  program will still print out the correct year for the overflowed integer.

## Execution Instructions

Life should be as simple as running `gcc -Wall -o PA1 PA1.c` and `./PA1` from
the root directory of the project. Once you run the program, it will ask that
you input a year. Simply type in a year, and you should be greeted with a
calendar for that year!

## Algorithm

In these sections, I will describe why I chose the implementation I did, how the
algorithm works, and a time complexity analysis.

### Reasoning

I had two main ideas when it came to designing this program. I could either:

1. Start off from a known year (1583) and iterate up to the inputted year
2. Mathematically calculate the first day of the month for the given year

I went with #2 in my implementation of the program, mostly for efficiency
reasons, which I will describe more in the Time Complexity Analysis section of
this document.

### How the algorithm works

For this program, I used the Key Value method to determine the day of week for
any date. The link to the math can be found 
![here](http://mathforum.org/dr.math/faq/faq.calendar.html). I chose this
algorithm over Zeller's method because I had trouble getting Zeller's rule to
actually work.

The math is based around the fact that the Gregorian Calendar repeats every 400
years. The exact details can be found on the website, but the basic gist of the
math is as follows:

1. Get the suffix of the year (ie, 2008 would be 08).
2. Divide by 4, as leap years occur roughly every 4 years
3. Add the date of the month
4. Apply a precalculated month modifier value
5. Add a leap year adjustment
6. Add a precalculated year modifier value
7. The modulo of 7 and get the day of week as a result

*Note*: When the modulo is taken, the days of the week are arranged in kind of a
weird way: Saturday is technically the start of the week. Not a big deal, but
just needs to be accounted for.

### Time Complexity Analysis

A naive solution to this problem would have been to start off with a known year,
and then work your way up/down to the desired year. While that works, that means
that you will have a loop that runs `O(n)` times, where `n` is the delta between
the desired year and the known year.

To alleviate this, I opted to calculate the first day of the week for every
month, and then to just generate the month from there. As all of the math is
formula based and has no loops, the whole program runs in `O(1)` time.

*Remarks:*
My code is sub-optimal because it calculates the first day of the week for every
month, instead of just calculating it once and generating the whole year from
there. My justification for this design is that the whole printMonth function is
a lot cleaner and easier to call. Additionally, because the cost to calculate
the first day of week of a month is `O(1)`, the performance loss is trivial.

Another place that my code could be optimized is to make the user inputted year
and other context associated flags global. I didn't implement my code this way,
as it's generally a **very** bad practice to make anything other than constants
global, even though it would have been perfectly acceptable in this case. While
the time complexity is trivial, the storage complexity would have been optimized
by keeping the values global.

## Loop Invariants 

### First for loop in printMonth()

This loop is in charge of filling up a month with blank to correctly align the
first day of week. My program was formatted to have 3 chars per date, and 2
chars per space between date. Thus, if the month started on the `n`th day, then
there would need to be `5 * n` spaces.

Thus the loop invariant is that the current value (`i`) represents every char
that is blank because there is no day on that month. The left side of the line
is always supposed to be nothing or just white space, and the right side of the
cursor should always have no text.

### Second for loop in printMonth()

This loop is responsible for printing each week in the month. The cursor goes on
for only 6 weeks as there are a max of 5 week in a month + 1 for safety (and
future-proofing against future formatting changes).

The loop invariant is that the current value represents the current week in the
month that is being printed out. Before the cursor, all of the previous
weeks/day headers should be printed out. After the cursor should be nothing.

### Third for loop in printMonth()

This loop prints out each day in a week. The loop variable is initialized to be
equal to `startPos` which is a variable storing the position of the first day of
week. Therefore, a pre-condition is that `startPos` is in the discrete range of
[0, 6]. Additionally, a post condition of the parent loop is that `startPos`
gets reset every iteration.

The loop invariant is that on the left side of the cursor is always either
white space, nothing, or the previous days of the week that have been already
printed out. The right side of the cursor should be nothing.

### First loop in printCalendar()

This loop prints out every month in the year.

The loop invariant is that the loop variable represents every month in the year.
Before the cursor should be previously printed out months, headings, or white
space, and after the cursor should be nothing.
