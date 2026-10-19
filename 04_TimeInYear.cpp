#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

short readNum(string message)
{
    short num;
    cout << message;
    cin >> num;

    return num;
}

bool leapYear(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || (year % 400 == 0));
}

array<int, 5> timeInYear(short &year)
{    
    unsigned short days  = 365   + leapYear(year);
    unsigned short hours = days  * 24;
    unsigned int   mins  = hours * 60;
    unsigned int   secs  = mins  * 60;

    array<int, 5> time = {year, days, hours, mins, secs};
    return time;
}

int main()
{
    short year = readNum("Please, enter a year: ");

    array<int, 5> time = timeInYear(year);
    array<string, 4> categories {"days", "hours", "minutes", "seconds"};

    cout << "\n";
    for (int i = 1; i < time.size(); ++i)
    {
        cout << "Number of " << setw(7) << left << categories[i - 1] << " in Year [" << time[0] << "] is " << time[i] << "\n"; 
    }

    return 0;
}