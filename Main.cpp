#include <iostream>
#include "transaction.h"
#include <ostream>
#include "user.h"
#include <vector>
#include <Windows.h>

using namespace std;

void welcome()
{
    string welcome1 = "Welcome To Project";
    cout << "\n\n\n\t";
    Sleep(250);
    for (int i = 0; welcome1[i]; i++)
    {
        Sleep(65);
        cout << welcome1[i];
    }
    Sleep(1000);
    system("cls");
}

int main()
{
    welcome();
    user temp;
    temp.menu();
    
    return 0;
}

