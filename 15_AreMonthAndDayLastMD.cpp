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

dateS readDate()
{
    dateS date;
    date.year = readNum("Please, enter a year: ", 0, 3000);
    date.month = readNum("Please, enter a month: ", 1, 12);
    date.day = readNum("Please, enter a day: ", 1, daysInMonth(date.year, date.month));
    cout << "\n";

    return date;
}

bool isLastMonth(short month)
{
    return month == 12;
}

bool isLastDay(dateS date)
{
    return date.day == daysInMonth(date.year, date.month);
}

int main()
{

    dateS date = readDate();

    cout << (isLastDay(date) ? "Yes" : "No") << ", input day is " << (isLastDay(date) ? "" : "not ") << "The last Day in month.\n";
    cout << (isLastMonth(date.month) ? "Yes" : "No") << ", input month is " << (isLastMonth(date.month) ? "" : "not ") << "The last month in year.";
    return 0;
}