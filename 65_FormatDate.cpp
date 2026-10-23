#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> splitStr(string s, char separator)
{
    vector<string> elements;
    string sub;
    s += separator;

    for (char ch : s)
    {
        if (ch == separator)
        {
            elements.push_back(sub);
            sub = "";
        }
        else
        {
            sub += ch;
        }
    }

    return elements;
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

bool isValidDate(dateS date)
{
    return (date.year > -1) && (date.month > 0 && date.month < 13) && (date.day > 0 && date.day <= daysInMonth(date.year, date.month));
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

string formatDate(dateS date, string format)
{
    short findDD = format.find("dd");
    if (findDD == -1) return "";

    format = format.substr(0, findDD) + to_string(date.day) + ((findDD + 2 < format.length()) ? format.substr(findDD + 2) : "");

    short findMM = format.find("mm");
    if (findMM == -1) return "";

    format = format.substr(0, findMM) + to_string(date.month) + ((findMM + 2 < format.length()) ? format.substr(findMM + 2) : "");

    short findYYYY = format.find("yyyy");
    if (findYYYY == -1) return "";

    format = format.substr(0, findYYYY) + to_string(date.year) + ((findYYYY + 4 < format.length()) ? format.substr(findYYYY + 4) : "");

    return format;
}

int main()
{
    dateS date = readDate();

    string strD = formatDate(date, "dd/mm/yyyy");
    cout << strD << "\n\n";

    strD = formatDate(date, "yyyy/dd/mm");
    cout << strD << "\n\n";

    strD = formatDate(date, "mm/dd/yyyy");
    cout << strD << "\n\n";

    strD = formatDate(date, "mm-dd-yyyy");
    cout << strD << "\n\n";

    strD = formatDate(date, "dd-mm-yyyy");
    cout << strD << "\n\n";

    strD = formatDate(date, "Day:dd, Month:mm, Year:yyyy");
    cout << strD << "\n\n";
    return 0;
}