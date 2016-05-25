#include "s_linked_list.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    s_linked_list<string> test_list;
    test_list.clear();

    test_list.add(0, "");

    system("pause");
    return 0;
}