// split_Identical_Characters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
std::vector<std::string> splitGroups(std::string s) {
    std::vector<std::string> splitString;
    char curChar;
    char prevChar = s[0];
    std::string newString;
    newString.push_back(prevChar);
    for (size_t i = 1; i < s.length(); i++)
    {
        curChar = s[i];
        if (curChar == prevChar)
        {
            newString.push_back(curChar);
            prevChar = curChar;
        }
        else
        {
            splitString.push_back(newString);
            newString.clear();
            prevChar = curChar;
            newString.push_back(curChar);
        }
    }
    if (!newString.empty())
    {
        splitString.push_back(newString);
        newString.clear();
    }
    // Display
    for (size_t i = 0; i < splitString.size(); i++)
    {
        std::cout << splitString[i] << std::endl;
    }
    std::cout << std::endl;
    return splitString;
}
int main()
{
    splitGroups("555"); //["555"]
    splitGroups("5556667788"); //["555", "666", "77", "88"]
    splitGroups("aaabbbaabbab"); //["aaa", "bbb", "aa", "bb", "a", "b"]
    splitGroups("abbbcc88999&&!!!_"); //["a", "bbb", "cc", "88", "999", "&&", "!!!", "_"]
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
