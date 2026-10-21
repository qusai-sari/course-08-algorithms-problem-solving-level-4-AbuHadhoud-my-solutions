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

unsigned short allDaysFromBeginningOfYear(dateS date)
{
    unsigned short sum = 0;
    for (int i = 1; i < date.month; ++i)
        sum += daysInMonth(date.year, i);

    return sum + date.day;
}

bool isDate1BeforeThan2(dateS date1, dateS date2)
{
    return (date1.year < date2.year) || ((date1.year == date2.year) && ((date1.month < date2.month) || (date1.month == date2.month) && (date1.day < date2.day)));
}

int main()
{

    dateS date1 = readDate();
    dateS date2 = readDate();

    cout << (isDate1BeforeThan2(date1, date2) ? "Yes" : "No") << ", Date1 is " << (isDate1BeforeThan2(date1, date2) ? "" : "not ") << "less than Date2.";
    return 0;
}