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

bool isDate1BeforeDate2(dateS date1, dateS date2)
{
    return (date1.year < date2.year) || ((date1.year == date2.year) && ((date1.month < date2.month) || (date1.month == date2.month) && (date1.day < date2.day)));
}

bool isDate1EqualDate2(dateS date1, dateS date2)
{
    return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day;
}

enum enCompareDatesResults {BEFORE = -1, EQUAL = 0, AFTER = 1};

enCompareDatesResults compare2Dates(dateS date1, dateS date2)
{
    return (isDate1BeforeDate2(date1, date2)? enCompareDatesResults::BEFORE : isDate1EqualDate2(date1, date2) ? enCompareDatesResults::EQUAL : enCompareDatesResults::AFTER);
}

struct periodS
{
    dateS startD, endD;
};

periodS readPeriod()
{
    periodS p;
    cout << "Enter the start date of the period:\n";
    p.startD = readDate();
    
    cout << "Enter the end date of the period:\n";
    p.endD = readDate();

    if (isDate1BeforeDate2(p.endD, p.startD))
    {
        dateS tempD = p.startD;
        p.startD = p.endD;
        p.endD = tempD;
    }

    return p;
}

bool arePeriodsOperlapped(periodS p1, periodS p2)
{
    return !(compare2Dates(p1.startD, p2.endD) == enCompareDatesResults::AFTER || compare2Dates(p1.endD, p2.startD) == enCompareDatesResults::BEFORE);
}


bool isDateWithinPeriod(periodS p, dateS date)
{
    periodS temp;
    temp.startD = date;
    temp.endD = date;
    return arePeriodsOperlapped(temp, p);
}

int main()
{
    periodS p = readPeriod();

    cout << "Enter date to check:\n";
    dateS date = readDate();

    cout << (isDateWithinPeriod(p, date) ? "Yes" : "No") << ", Date is " << (isDateWithinPeriod(p, date) ? "" : "not ") << "within period";
    return 0;
}