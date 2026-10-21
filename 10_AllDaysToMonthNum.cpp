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
    if (month < 1 || month > 12) return 0;
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && leapYear(year));
}

unsigned short allDaysToMonthNum(short year, short month, short day)
{
    unsigned short sum = 0;
    for (int i = 1; i < month; ++i)
        sum += daysInMonth(year, i);

    return sum + day;
}

int main()
{
    short year = readNum("Please, enter a year: ", 0, 3000);
    short month = readNum("Please, enter a month: ", 1, 12);
    short day = readNum("Please, enter a day: ", 1, daysInMonth(year, month));

    cout << "\nNumber of days from the beginning of the year is " << allDaysToMonthNum(year, month, day);

    return 0;
}