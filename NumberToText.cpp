#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<string> place = {"", "Thousands", "Millions", "Billions"};
map<int, string> mainNTxt = {{0, ""}, {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}};

long long readNum(string message)
{
    long long num;
    cout << message;
    cin >> num;

    return num;
}

string numToText(long long num)
{
    vector<int> treplits;

    short treplit;
    while (num > 0)
    {
        treplit = num % 1000;
        num /= 1000;
        treplits.push_back(treplit);
    }

    string Numstr;
    for (int i = treplits.size() - 1; i >= 0; --i)
    {
        int hundreds = treplits[i] / 100;
        int tens = (treplits[i] / 10) % 10;
        int units = treplits[i] % 10;

        auto it = mainNTxt.find(treplits[i] % 100);
        Numstr += (mainNTxt[hundreds] + ((hundreds != 0) ? " hundreds" : "") + ((hundreds != 0 && (tens | units != 0)) ? " " : "") + ((it != mainNTxt.end()) ? it->second : (mainNTxt[tens * 10] + ((tens != 0) ? " " : "") + mainNTxt[units]))) + " " + place[i] + " ";
    }

    return Numstr;
}

void runSystem()
{
    long long num = readNum("Enter a number to get it in a text form: ");

    cout << "\n"
         << numToText(num);
}

int main()
{
    runSystem();
    return 0;
}