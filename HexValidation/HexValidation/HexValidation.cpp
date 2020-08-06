// HexValidation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
bool IntConversion(int isuppernum){
    if (isuppernum == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool isValidHexCode(std::string str)
{
    bool uppercase;
    if (str.length() > 7)
    {
        return false;
    }
    if (str[0] != '#')
    {
        return false;
    }
    if (!std::isdigit(str[1]))
    {
        uppercase = IntConversion(std::isupper(str[1]));
    }
    for (size_t i = 1; i < str.length(); i++)
    {
        if (IntConversion(std::isupper(str[i])) != uppercase && !std::isdigit(str[i]))
        {
            return false;
        }
        str[i] = std::tolower(str[i]);
        if ((str[i] < 'a' || str[i] > 'f') && !std::isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}
int main()
{
    std::cout << isValidHexCode("#CD5C5C") << std::endl;// true
    std::cout << isValidHexCode("#EAECEE") << std::endl;// true
    std::cout << isValidHexCode("#eaecee") << std::endl;// true
    std::cout << isValidHexCode("#CD5C58C") << std::endl;// false
    // Length exceeds 6
    std::cout << isValidHexCode("#CD5C5Z") << std::endl;// false
    // Not all alphabetic characters in A-F
    std::cout << isValidHexCode("#CD5C&C") << std::endl;// false
    // Contains unacceptable character
    std::cout << isValidHexCode("CD5C5C") << std::endl;// false
    // Missing #
    std::cout << isValidHexCode("#cd5C5D") << std::endl;// false
    // all aplphabetic characters must match in case
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
