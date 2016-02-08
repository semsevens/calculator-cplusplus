/*
* Entry file of calculator
*
* By semsevens
*
* Simple calculate
*
*/

#include <iostream>
#include "ex.h"
using std::cin;
using std::cout;
using std::endl;

int main(void)
{
    String temp;
    cin >> temp;
    Ex a(temp);
    cout << "= " << a.val() << endl;
    cin.get();
    return 0;
}
