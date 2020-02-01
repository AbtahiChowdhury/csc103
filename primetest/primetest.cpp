#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned long input, divide, output=2;
    while (cin >> input)
    {
        if (input == 0 || input == 1)
        {
            cout << 0 << endl;
        }
        else
        {
            divide = input - 1;
        }
        while(divide > 1)
        {
            if (input % divide == 0)
            {
                output = 0;
                break;
            }
            else
            {
                divide--;
            }
        }
        if (output == 2)
        {
            output = 1;
        }
        cout << output << endl;
        output = 2;
    }
    return 0;
}
