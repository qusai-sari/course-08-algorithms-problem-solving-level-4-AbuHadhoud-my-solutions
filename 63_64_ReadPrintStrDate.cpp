#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

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

bool isValidDate(dateS date)
{
    return (date.year > -1) && (date.month > 0 && date.month < 13) && (date.day > 0 && date.day <= daysInMonth(date.year, date.month));
}

void displayDate(dateS date)
{
    cout << date.day << "/" << date.month << "/" << date.year;
}

dateS readDate()
{
    string strD;
    dateS date;
    do
    {
        cout << "Please enter valid date dd/mm/yyyy: ";
        cin >> strD;
        strD += "/";
        cout << "\n";

        vector<short> parts(3);
        short subDate = 0, i = 0;
        for (char ch : strD)
        {
            if (isdigit(ch))
            {
                subDate *= 10;
                subDate += ch - '0';
            }
            else if (ch == '/')
            {
                if (i > 2)
                    break;

                parts[i++] = subDate;
                subDate = 0;
            }
        }

        date.day = parts[0];
        date.month = parts[1];
        date.year = parts[2];
    } while (!isValidDate(date));

    return date;
}

int main()
{
    dateS date = readDate();

    cout << "Day: " << date.day << "\n";
    cout << "month: " << date.month << "\n";
    cout << "year: " << date.year << "\n\n";

    cout << "You entered: ";
    displayDate(date);
    return 0;
}