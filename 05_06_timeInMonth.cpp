#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

short readNum(const string &message, short smallest = -35000, short biggest = 35000)
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
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && leapYear(year));
}

unsigned short hoursInMonth(short year, short month)
{
    return daysInMonth(year, month) * 24;
}

unsigned minsInMonth(short year, short month)
{
    return hoursInMonth(year, month) * 60;
}

unsigned secsInMonth(short year, short month)
{
    return minsInMonth(year, month) * 60;
}

int main()
{
    short year = readNum("Please, enter a year: ", 0, 3000);
    short month = readNum("\nPlease, enter a month: ", 1, 12);

    cout << "\n";

    cout << "Number of " << setw(7) << left << "days"    << " in month [" << month << "] is " << daysInMonth(year, month) << "\n";
    cout << "Number of " << setw(7) << left << "hours"   << " in month [" << month << "] is " << hoursInMonth(year, month) << "\n";
    cout << "Number of " << setw(7) << left << "minutes" << " in month [" << month << "] is " << minsInMonth(year, month) << "\n";
    cout << "Number of " << setw(7) << left << "seconds" << " in month [" << month << "] is " << secsInMonth(year, month) << "\n";

    return 0;
}