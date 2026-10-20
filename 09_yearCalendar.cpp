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

array<array<unsigned short, 7>, 6> makeMonthCalendar(short year, short month)
{
    unsigned short startingDayOrder = dayOrder(year, month, 1), count = 1, daysNum = daysInMonth(year, month);
    array<array<unsigned short, 7>, 6> monthCalendar{};

    int j = startingDayOrder;
    for (int i = 0; i < monthCalendar.size(); ++i)
    {
        for (; j < monthCalendar[0].size() && count <= daysNum; ++j)
            monthCalendar[i][j] = count++;

        j = 0;
    }

    return monthCalendar;
}

void displayMonthCalendar(short year, short month)
{
    string monthName[13]{"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    array<array<unsigned short, 7>, 6> monthCalendar = makeMonthCalendar(year, month);

    cout << "  _______________" << monthName[month] << "_______________  \n\n";
    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat  \n";

    for (int i = 0; i < monthCalendar.size() && !(i > 0 && monthCalendar[i][0] == 0); ++i)
    {
        for (int j = 0; j < monthCalendar[0].size(); ++j)
            if (monthCalendar[i][j] != 0)
                printf("%5d", monthCalendar[i][j]);
            else
                printf("     ");
        cout << "\n";
    }

    cout << "  _________________________________  \n\n";
}

void displayYearCalendar(short year)
{
    cout << "  _________________________________\n\n";
    cout << "           Calendar - " << year << "\n";
    cout << "  _________________________________\n\n";

    for (int i = 1; i <= 12; ++i)
        displayMonthCalendar(year, i);
}

int main()
{
    short year = readNum("Please, enter a year: ", 0, 3000);

    cout << "\n";
    displayYearCalendar(year);
    return 0;
}