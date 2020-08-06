// OddNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
std::vector<int> Sort(std::vector<int> arr)
{
    bool sorted = false;
    int temp;
    while (sorted == false)
    {
        sorted = true;
        for (size_t i = 0; i < arr.size()-1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                sorted = false;
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    return arr;
}
int findOdd(std::vector<int> arr) {
    arr = Sort(arr);
    int curVal;
    int preVal = NULL;
    int count = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        curVal = arr[i];
        if (preVal == NULL)
        {
            count = 1;
        }
        else if (curVal != preVal)
        {
            if (count % 2 == 1)
            {
                return preVal;
            }
            count = 1;
        }
        else
        {
            count++;
        }
        if (i == arr.size()-1)
        {
            if (count % 2 == 1)
            {
                return curVal;
            }
        }
        preVal = curVal;
    }
    return NULL;
}
int main()
{
    std::cout << findOdd({ 1, 1, 2, -2, 5, 2, 4, 4, -1, -2, 5 }) << std::endl; // return -1
    std::cout << findOdd({ 20, 1, 1, 2, 2, 3, 3, 5, 5, 4, 20, 4, 5 }) << std::endl; // return 5
    std::cout << findOdd({ 10 }) << std::endl; // return 10
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
