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
    date.year = readNum("Please, enter a year: ", 0, 5000);
    date.month = readNum("Please, enter a month: ", 1, 12);
    date.day = readNum("Please, enter a day: ", 1, daysInMonth(date.year, date.month));
    cout << "\n";

    return date;
}

dateS decreaseDateByNDays(dateS date, unsigned int daysToSub)
{
    unsigned short remainingDaysOfMonth = date.day;

    while (daysToSub >= remainingDaysOfMonth)
    {
        if (--date.month < 1)
        {
            date.month = 12;
            --date.year;
        }

        date.day = daysInMonth(date.year, date.month);
        daysToSub -= remainingDaysOfMonth;

        remainingDaysOfMonth = daysInMonth(date.year, date.month);
    }
    date.day -= daysToSub;

    return date;
}

dateS decreaseDateByOneDay(dateS date)
{
    return decreaseDateByNDays(date, 1);
}

dateS decreaseDateByOneWeek(dateS date)
{
    return decreaseDateByNDays(date, 7);
}

dateS decreaseDateByNWeeks(dateS date, unsigned short weeks)
{
    return decreaseDateByNDays(date, 7 * weeks);
}

dateS decreaseDateByOneMonth(dateS date)
{    
    if (--date.month < 1)
    {
        date.month = 12;
        --date.year;
    }

    if (date.day > daysInMonth(date.year, date.month))
        date.day = daysInMonth(date.year, date.month);

    return date;
}

dateS decreaseDateByNMonths(dateS date, unsigned short months)
{
    for (int i = 1; i <= months; ++i)
        date = decreaseDateByOneMonth(date);

    return date;
}

dateS decreaseDateByOneYear(dateS date)
{
    --date.year;
    return date;
}

dateS decreaseDateByNYears(dateS date, unsigned short years)
{
    for (int i = 0; i < years; ++i)
        date = decreaseDateByOneYear(date);

    return date;
}

dateS decreaseDateByNYearsFaster(dateS date, unsigned short years)
{
    date.year -= years;
    return date;
}

dateS decreaseDateByOneDecade(dateS date)
{
    date = decreaseDateByNYearsFaster(date, 10);
    return date;
}

dateS decreaseDateByNDecades(dateS date, unsigned short decades)
{
    for (int i = 1; i <= decades; ++i)
        date = decreaseDateByOneDecade(date);
    return date;
}

dateS decreaseDateByNDecadesFaster(dateS date, unsigned short decades)
{
    date.year -= 10 * decades;
    return date;
}

dateS decreaseDateByOneCentury(dateS date)
{
    date.year -= 100;
    return date;
}

dateS decreaseDateByOneMillennium(dateS date)
{
    date.year -= 1000;
    return date;
}

int main()
{

    dateS date = readDate();

    date = decreaseDateByOneDay(date);
    cout << "\n01-Date after subtracting one day is:             " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNDays(date, 10);
    cout << "\n02-Date after subtracting 10 day is:              " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneWeek(date);
    cout << "\n03-Date after subtracting one week is:            " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNWeeks(date, 10);
    cout << "\n04-Date after subtracting 10 weeks is:            " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneMonth(date);
    cout << "\n05-Date after subtracting one month is:           " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNMonths(date, 5);
    cout << "\n06-Date after subtracting 5 months is:            " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneYear(date);
    cout << "\n07-Date after subtracting one year is:            " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNYears(date, 10);
    cout << "\n08-Date after subtracting 10 years is:            " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNYearsFaster(date, 10);
    cout << "\n09-Date after subtracting 10 years (faster) is:   " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneDecade(date);
    cout << "\n10-Date after subtracting one decade is:          " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNDecades(date, 10);
    cout << "\n11-Date after subtracting 10 Decades is:          " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByNDecadesFaster(date, 10);
    cout << "\n12-Date after subtracting 10 Decades (faster) is: " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneCentury(date);
    cout << "\n13-Date after subtracting one century is:         " << date.day << "/" << date.month << "/" << date.year;

    date = decreaseDateByOneMillennium(date);
    cout << "\n14-Date after subtracting one millennium is:      " << date.day << "/" << date.month << "/" << date.year;

    return 0;
}