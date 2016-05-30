#include <iostream>
#include <string>
#include <vector>
#include "timer.h"
#include "dsa.h"

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
        for (size_t i = 0; i < 1000; i++)
        {
            test_list1.insert(test_list1.end(),
                std::to_string(i));
        }
        for (size_t i = 0; i < 1000; i++)
        {
            test_list1.erase(test_list1.begin());
        }
        total_time1 += t.elapsed();
        test_list1.clear();
    }
    std::cout << total_time1 / COUNT << "s" << std::endl;
    /**/
    /**/
    std::cout << "Testing DSA::s_linked_list<string>..." << std::endl;
    s_linked_list<string> test_list2;
    double total_time2 = 0;
    for (size_t i = 0; i < COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < 1000; i++)
        {
            test_list2.add(std::to_string(i));
        }
        for (size_t i = 0; i < 1000; i++)
        {
            test_list2.remove(0);
        }
        total_time2 += t.elapsed();
        test_list2.clear();
    }
    std::cout << total_time2 / COUNT << "s" << std::endl;
    /**/

    std::cout << "Testing DSA::array_list<string>..." << std::endl;
    array_list<string> test_list3(1000);
    double total_time3 = 0;
    for (size_t i = 0; i < COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < 1000; i++)
        {
            test_list3.add(std::to_string(i));
        }
        for (size_t i = 0; i < 1000; i++)
        {
            test_list3.remove(0);
        }
        total_time3 += t.elapsed();
        test_list3.clear();
    }
    std::cout << total_time3 / COUNT << "s" << std::endl;


    system("pause");
    return 0;
}