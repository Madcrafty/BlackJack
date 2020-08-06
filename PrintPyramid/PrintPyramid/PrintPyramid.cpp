// PrintPyramid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
void print_pyramid(int height)
{
    if (height > 0)
    {
        std::string pyramid;
        for (size_t i = 0; i < height; i++)
        {
            pyramid.push_back(' ');
        }
        for (size_t i = 0; i < height; i++)
        {
            pyramid.erase(pyramid.begin());
            pyramid.push_back('*');
            pyramid.push_back('*');
            std::cout << pyramid << std::endl;
        }
    }
    if (height < 0)
    {
        std::string pyramid;
        for (size_t i = 0; i < -height; i++)
        {
            pyramid.push_back('*');
            pyramid.push_back('*');
        }
        for (size_t i = 0; i < -height; i++)
        {
            std::cout << pyramid << std::endl;
            pyramid.pop_back();
            pyramid.pop_back();
            pyramid.insert(pyramid.begin(), ' ');
        }
    }
    else
    {
        return;
    }
}
int main()
{
    std::cout << "=======================================" << std::endl;
    print_pyramid(6);
    std::cout << "=======================================" << std::endl;
    print_pyramid(7);
    std::cout << "=======================================" << std::endl;
    print_pyramid(-1);
    std::cout << "=======================================" << std::endl;
    print_pyramid(-6);
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
