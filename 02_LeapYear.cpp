#include <iostream>

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
    return (year % 4 == 0) && (year % 100 == 0 ? (year % 400 == 0) : true);
}

int main()
{

    short year = readNum("Enter a year to know if it's leap: ");
    cout << "\n" << (leapYear(year)  ? "Leap Year" : "Not Leap Year");

    return 0;
}