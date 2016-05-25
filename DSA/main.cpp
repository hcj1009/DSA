#include "s_linked_list.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    string test_array[100];
    for (size_t i = 0; i < 100; i++)
    {
        test_array[i] = to_string(i);
    }

    s_linked_list<string> list;
    s_linked_list<string> list2(test_array, 100);

    system("pause");
    return 0;
}