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

dateS increaseDateByNDays(dateS date, unsigned int daysToAdd)
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

dateS increaseDateByOneDay(dateS date)
{
    return increaseDateByNDays(date, 1);
}

dateS increaseDateByOneWeek(dateS date)
{
    return increaseDateByNDays(date, 7);
}

dateS increaseDateByNWeeks(dateS date, unsigned short weeks)
{
    return increaseDateByNDays(date, 7 * weeks);
}

dateS increaseDateByOneMonth(dateS date)
{
    ++date.month;
    
    if (date.month > 12)
    {
        date.month = 1;
        ++date.year;
    }

    if (date.day > daysInMonth(date.year, date.month))
        date.day = daysInMonth(date.year, date.month);

    return date;
}

dateS increaseDateByNMonths(dateS date, unsigned short months)
{
    for (int i = 1; i <= months; ++i)
        date = increaseDateByOneMonth(date);

    return date;
}

dateS increaseDateByOneYear(dateS date)
{
    ++date.year;
    return date;
}

dateS increaseDateByNYears(dateS date, unsigned short years)
{
    for (int i = 0; i < years; ++i)
        date = increaseDateByOneYear(date);

    return date;
}

dateS increaseDateByNYearsFaster(dateS date, unsigned short years)
{
    date.year += years;
    return date;
}

dateS increaseDateByOneDecade(dateS date)
{
    date = increaseDateByNYearsFaster(date, 10);
    return date;
}

dateS increaseDateByNDecades(dateS date, unsigned short decades)
{
    for (int i = 1; i <= decades; ++i)
        date = increaseDateByOneDecade(date);
    return date;
}

dateS increaseDateByNDecadesFaster(dateS date, unsigned short decades)
{
    date = increaseDateByNYearsFaster(date, 10 * decades);
    return date;
}

dateS increaseDateByOneCentury(dateS date)
{
    date = increaseDateByNYearsFaster(date, 100);
    return date;
}

dateS increaseDateByOneMillennium(dateS date)
{
    date = increaseDateByNYearsFaster(date, 1000);
    return date;
}

int main()
{

    dateS date = readDate();

    date = increaseDateByOneDay(date);
    cout << "\n01-Date after adding one day is:             " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNDays(date, 10);
    cout << "\n02-Date after adding 10 day is:              " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneWeek(date);
    cout << "\n03-Date after adding one week is:            " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNWeeks(date, 10);
    cout << "\n04-Date after adding 10 weeks is:            " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneMonth(date);
    cout << "\n05-Date after adding one month is:           " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNMonths(date, 5);
    cout << "\n06-Date after adding 5 months is:            " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneYear(date);
    cout << "\n07-Date after adding one year is:            " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNYears(date, 10);
    cout << "\n08-Date after adding 10 years is:            " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNYearsFaster(date, 10);
    cout << "\n09-Date after adding 10 years (faster) is:   " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneDecade(date);
    cout << "\n10-Date after adding one decade is:          " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNDecades(date, 10);
    cout << "\n11-Date after adding 10 Decades is:          " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByNDecadesFaster(date, 10);
    cout << "\n12-Date after adding 10 Decades (faster) is: " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneCentury(date);
    cout << "\n13-Date after adding one century is:         " << date.day << "/" << date.month << "/" << date.year;

    date = increaseDateByOneMillennium(date);
    cout << "\n14-Date after adding one millennium is:      " << date.day << "/" << date.month << "/" << date.year;

    return 0;
}