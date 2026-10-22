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

string dayName(unsigned short dayOrder)
{
    string dayNames[7]{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dayNames[dayOrder];
}

void displayDate(dateS date)
{
    cout << date.day << "/" << date.month << "/" << date.year;
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

int twoDatesDiff(dateS date1, dateS date2, bool isLastDayExclusive = 0)
{
    int diff = 0;

    if (date1.year < date2.year)
    {
        dateS tempDate = date1;
        tempDate.month = 12;
        tempDate.day = 31;
        diff += allDaysFromBeginningOfYear(tempDate) - allDaysFromBeginningOfYear(date1) + 1;

        ++tempDate.year;
        while (tempDate.year < date2.year)
        {
            diff += allDaysFromBeginningOfYear(tempDate);
            ++tempDate.year;
        }

        diff += allDaysFromBeginningOfYear(date2) - isLastDayExclusive;
    }
    else if (date1.year == date2.year && isDate1BeforeThan2(date1, date2))
    {
        diff = allDaysFromBeginningOfYear(date2) - allDaysFromBeginningOfYear(date1) + 1 - isLastDayExclusive;
    }
    else
    {
        diff = -twoDatesDiff(date2, date1, isLastDayExclusive);
    }

    return diff;
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

unsigned short vacationDaysBetween2Dates(dateS date1, dateS date2)
{
    unsigned short vacationDays = 0;
    while (isDate1BeforeThan2(date1, date2))
    {
        if (dayOrder(date1) < 5)
            ++vacationDays;

        date1 = increaseDateByNDays(date1, 1);
    }

    return vacationDays;
}

int main()
{
    cout << "Vacation starts: \n";
    dateS date1 = readDate();

    cout << "Vacation ends: \n";
    dateS date2 = readDate();

    unsigned short VacStartDayOrder = dayOrder(date1);
    unsigned short VacEndDayOrder = dayOrder(date2);

    cout << "Vacation From: " << dayName(VacStartDayOrder) << " , ";
    displayDate(date1);
    cout << "\n";

    cout << "Vacation To: " << dayName(VacEndDayOrder) << " , ";
    displayDate(date2);
    cout << "\n\n";

    cout << "Actual vacation days are: " << vacationDaysBetween2Dates(date1, date2);

    return 0;
}