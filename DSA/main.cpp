#include "array_list.h"
#include <string>
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    string test_array[100];
    for (size_t i = 0; i < 100; i++)
    {
        test_array[i] = "String";
    }
    array_list<string> test_list(test_array, 100);
    for (size_t i = 0; i < 100; i++)
    {
        try
        {
            test_list.remove(0);
        }
        catch (runtime_error e)
        {
            cout << i << ": " << e.what() << endl;
        }
    }

    system("pause");
    return 0;
}