/**
 * demonstration of pass by value
 * compared to pass by reference
*/
#include <iostream>

using std::cout;

// function prototype
void changeMyData(char& charRef, char charVal);

int
main(int argc, char* argv[])
{
    char a = 'A';
    char b = 'B';

    changeMyData(a, b);

    cout << "Value of a is: " << a << "\n";
    cout << "Value of b is: " << b << "\n";
}

void
changeMyData(char& charRef, char charVal)
{
    charRef = 'Z';
    charVal = 'Y';
}