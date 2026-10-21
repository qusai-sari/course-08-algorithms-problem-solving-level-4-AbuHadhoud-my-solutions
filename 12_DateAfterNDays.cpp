#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

short readNum(const string &message, short smallest = -30500, short biggest = 30500)
{
    short num;
    while (true)
    {
        cout << message;
        cin >> num;
        if (num < smallest || num > biggest)
            cout << "\nThe input number must be between " << smallest << " - " << biggest << "\n";
        else
            break;
    }

    return num;
}

bool leapYear(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || (year % 400 == 0));
}

unsigned short daysInMonth(short year, short month)
{
    if (month < 1 || month > 12)
        return 0;
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && leapYear(year));
}

struct dateS
{
    short year, month, day;
};

unsigned short allDaysFromBeginningOfYear(dateS date)
{
    unsigned short sum = 0;
    for (int i = 1; i < date.month; ++i)
        sum += daysInMonth(date.year, i);

    return sum + date.day;
}

dateS dateByYearAndDays(short year, short daysFromBeginningOfYear)
{
    dateS date;

    date.year = year;
    date.month = 0;
    while (daysFromBeginningOfYear > 0)
    {
        date.day = daysFromBeginningOfYear;
        daysFromBeginningOfYear -= daysInMonth(year, ++date.month);
    }

    return date;
}

dateS dateAfterNDays(dateS date, unsigned int daysToAdd)
{
    unsigned short remainingDaysOfMonth = daysInMonth(date.year, date.month) - date.day;

    while (daysToAdd > remainingDaysOfMonth)
    {
        if (++date.month > 12)
        {
            date.month = 1;
            ++date.year;
        }

        date.day = 0;
        daysToAdd -= remainingDaysOfMonth;

        remainingDaysOfMonth = daysInMonth(date.year, date.month);
    }
    date.day += daysToAdd;

    return date;
}

int main()
{
    dateS date;
    date.year = readNum("Please, enter a year: ", 0, 3000);
    date.month = readNum("Please, enter a month: ", 1, 12);
    date.day = readNum("Please, enter a day: ", 1, daysInMonth(date.year, date.month));
    unsigned int daysToAdd = readNum("How many days to add? ", 0);

    dateS dateAfterAddingDays = dateAfterNDays(date, daysToAdd);
    cout << "\nDate after adding [" << daysToAdd << "] days is: " << dateAfterAddingDays.day << "/" << dateAfterAddingDays.month << "/" << dateAfterAddingDays.year;
    return 0;
}