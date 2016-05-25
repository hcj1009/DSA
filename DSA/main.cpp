#include "array_list.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    string test_array[100];
    for (int i = 0; i < 100; i++)
    {
        test_array[i] = to_string(i);
    }

    // Default constructor.
    array_list<string> test_list1;

    // Constructor based on C array.
    array_list<string> test_list2(test_array, 100);

    // Default constructor (specified BASE_CAPACITY)
    array_list<string, 50> test_list3;

    // Constructor based on C array. (specified BASE_CAPACITY)
    array_list<string, 50> test_list4(test_array, 100);

    // Constructor based on List data structure.
    array_list<string> test_list5(test_list2);

    // Constructor based on List data structure.
    // (specified BASE_CAPACITY)
    array_list<string, 50> test_list6(test_list4);

    system("pause");
    return 0;
}