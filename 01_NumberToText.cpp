#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> place = {"", "Thousand", "Million", "Billion"};

map<int, string> mainNTxt = {{0, ""}, {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}, {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"}, {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"}, {20, "Twenty"}, {30, "Thirty"}, {40, "Forty"}, {50, "Fifty"}, {60, "Sixty"}, {70, "Seventy"}, {80, "Eighty"}, {90, "Ninety"}};

long long readNum(string message)
{
    long long num;
    cout << message;
    cin >> num;

    return num;
}

string numToText(long long num)
{
    if (num == 0) return "Zero";

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
        if (treplits[i] == 0) continue;

        int hundreds = treplits[i] / 100;
        int tens = (treplits[i] / 10) % 10;
        int units = treplits[i] % 10;

        auto it = mainNTxt.find(treplits[i] % 100);

        Numstr += (mainNTxt[hundreds] + ((hundreds != 0) ? " hundred" : "") + ((hundreds != 0 && (tens != 0 || units != 0)) ? " " : "") + ((it != mainNTxt.end()) ? it->second : (mainNTxt[tens * 10] + ((tens != 0) ? " " : "") + mainNTxt[units]))) + (place[i].empty() ? "" : " " + place[i]) + " ";
    }

    return Numstr;
}

void runSystem()
{
    long long num = readNum("Enter a number to get it in a text form: ");

    cout << "\n" << numToText(num);
}

int main()
{
    runSystem();
    return 0;
}