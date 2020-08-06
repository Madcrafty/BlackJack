// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
bool overTwentyOne(std::vector<char> cards) {
    int count = 0;
    int ace = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        if (cards[i] >= '2' && cards[i] <= '9')
        {
            count += cards[i] - 48;
        }
        if (cards[i] == 'J' || cards[i] == 'Q' || cards[i] == 'K')
        {
            count += 10;
        }
        if (cards[i] == 'A')
        {
            count += 11;
            ace++;
        }
        if (count > 21)
        {
            if (ace > 0)
            {
                count -= 10;
                ace--;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    std::cout << overTwentyOne({ '2', '8', 'J' }) << std::endl; // false
    std::cout << overTwentyOne({ 'A', 'J', 'K' }) << std::endl; // false
    std::cout << overTwentyOne({ '5', '5', '3', '9' }) << std::endl; // true
    std::cout << overTwentyOne({ '2', '6', '4', '4', '5' }) << std::endl;// false
    std::cout << overTwentyOne({ 'J', 'Q', 'K' }) << std::endl;// true
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
