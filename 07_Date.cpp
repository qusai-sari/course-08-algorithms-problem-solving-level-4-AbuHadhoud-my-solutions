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
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && leapYear(year));
}

unsigned short dayOrder(short year, short month, short day)
{
    year -= (month == 1 || month == 2);

    int monthsOrder[13]{0, 13, 14, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    short q = day;
    short m = monthsOrder[month];
    short k = year % 100;
    short j = year / 100;

    // Zeller's Congruence
    short h = (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + 5 * j) % 7; // Saturday = 0

    return (h + 6) % 7; // Sunday = 0
}

string dayName(unsigned short dayOrder)
{
    string dayNames[7]{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dayNames[dayOrder];
}

int main()
{
    short year  = readNum("Please, enter a year: ", 0, 3000);
    short month = readNum("\nPlease, enter a month: ", 1, 12);
    short day   = readNum("\nPlease, enter a day: ", 1, daysInMonth(year, month));

    cout << "\n";
    cout << setw(11) << left << "Date:" << day << "/" << month << "/" << year << "\n";
    cout << setw(11) << left << "Day Order:" << dayOrder(year, month, day) << "\n";
    cout << setw(11) << left << "Day Name:" << dayName(dayOrder(year, month, day)) << "\n";

    return 0;
}