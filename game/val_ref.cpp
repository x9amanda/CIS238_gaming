/**
 * demonstration of pass by value
 * compared to pass by reference
*/
#include <iostream>

using std::cout;

// function prototype
void changeMyData(char& charRef, char charVal, char* charPtr);

int
main(int argc, char* argv[])
{
    char a = 'A';
    char b = 'B';

    changeMyData(a, b, &a);

    cout << "Value of a is: " << a << "\n";
    cout << "Value of b is: " << b << "\n";
    cout << "Value of &a is: " << &a << "\n";

}

void
changeMyData(char& charRef,
char charVal, char* charPtr)
{
    charRef = 'Z';
    charVal = 'Y';

    *charPtr = 'X';
}