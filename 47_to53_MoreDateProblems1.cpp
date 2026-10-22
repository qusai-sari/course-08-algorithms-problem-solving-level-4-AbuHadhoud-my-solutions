#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

bool leapYear(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || (year % 400 == 0));
}

unsigned short daysInMonth(short year, short month)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && leapYear(year));
}

struct dateS
{
    short year, month, day;
};

unsigned short dayOrder(dateS date)
{
    date.year -= (date.month == 1 || date.month == 2);

    int monthsOrder[13]{0, 13, 14, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    short q = date.day;
    short m = monthsOrder[date.month];
    short k = date.year % 100;
    short j = date.year / 100;

    // Zeller's Congruence
    short h = (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + 5 * j) % 7; // Saturday = 0

    return (h + 6) % 7; // Sunday = 0
}

string dayName(unsigned short dayOrderVal)
{
    string dayNames[7]{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dayNames[dayOrderVal];
}

bool isEndOfWeek(unsigned short dayOrderVal)
{
    return dayOrderVal == 6;
}

bool isWeekend(unsigned short dayOrderVal)
{
    return dayOrderVal == 5 || dayOrderVal == 6;
}

bool isBussinessDay(unsigned short dayOrderVal)
{
    return !isWeekend(dayOrderVal);
}

unsigned short daysUntilEndOfWeek(unsigned short dayOrderVal)
{
    return 6 - dayOrderVal;
}

unsigned short daysUntilEndOfMonth(dateS date)
{
    return daysInMonth(date.year, date.month) - date.day + 1;
}

unsigned short allDaysFromBeginningOfYear(dateS date)
{
    unsigned short sum = 0;
    for (int i = 1; i < date.month; ++i)
        sum += daysInMonth(date.year, i);

    return sum + date.day;
}

unsigned int daysUntilEndOfYear(dateS date)
{
    dateS endDate;
    endDate.year = date.year;
    endDate.month = 12;
    endDate.day = 31;

    return allDaysFromBeginningOfYear(endDate) - allDaysFromBeginningOfYear(date) + 1;
}

dateS systemDate()
{
    dateS date;
    time_t t = time(0);
    tm *now = localtime(&t);

    date.year = now->tm_year + 1900;
    date.month = now->tm_mon + 1;
    date.day = now->tm_mday;

    return date;
}

int main()
{
    dateS date = systemDate();

    unsigned short dayOrderVal = dayOrder(date);

    cout << "Today, is " << dayName(dayOrderVal) << " , " << date.day << "/" << date.month << "/" << date.year;
    
    cout << "\n\nIs it end of week?\n";
    cout << (isEndOfWeek(dayOrderVal) ? "Yes" : "No") << ", it is " << (isEndOfWeek(dayOrderVal) ? "" : "not ") << "end of the week.";
    
    cout << "\n\nIs it weekend?\n";
    cout << (isWeekend(dayOrderVal) ? "Yes" : "No") << ", it is " << (isWeekend(dayOrderVal) ? "" : "not ") << "a weekend.";
    
    cout << "\n\nIs it a bussiness day?\n";
    cout << (isBussinessDay(dayOrderVal) ? "Yes" : "No") << ", it is " << (isBussinessDay(dayOrderVal) ? "" : "not ") << "a bussiness day.\n";

    cout << "\nDays until the end of the week : " << daysUntilEndOfWeek(dayOrderVal) << " Day(s)";
    cout << "\nDays until the end of the month: " << daysUntilEndOfMonth(date) << " Day(s)";
    cout << "\nDays until the end of the year : " << daysUntilEndOfYear(date) << " Day(s)";
    return 0;
}