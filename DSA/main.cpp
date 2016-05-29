#include <iostream>
#include <string>
#include <vector>
#include "timer.h"
#include "dsa.h"

#include "dsa_object.h"

using namespace DSA;
using DSA::utility::timer;

const size_t COUNT = 100;

int main(int argc, char *argv[])
{
    timer t;

    /**
    std::cout << "Testing std::vector<string>..." << std::endl;
    std::vector<std::string> test_list1;
    double total_time1 = 0;
    for (size_t i = 0; i < COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < 10000; i++)
        {
            test_list1.insert(test_list1.end(),
                std::to_string(i));
        }
        total_time1 += t.elapsed();
        test_list1.clear();
    }
    std::cout << total_time1 / COUNT << "s" << std::endl;
    /**/

    /**/
    std::cout << "Testing DSA::array_list<string>..." << std::endl;
    array_list<string> test_list2(5000);
    double total_time2 = 0;
    for (size_t i = 0; i < COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < 10000; i++)
        {
            test_list2.add(std::to_string(i));
        }
        total_time2 += t.elapsed();
        test_list2.clear();
    }
    std::cout << total_time2 / COUNT << "s" << std::endl;
    /**/


    system("pause");
    return 0;
}