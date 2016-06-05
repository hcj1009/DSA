#include <iostream>
#include <string>

#include "timer.h"
//#include "dsa.h"
#include <iterator>
#include "std_container.h"
#include "dynamic_array_container.h"

using DSA::dynamic_array_container;
using DSA::utility::timer;

//const size_t ITEM_COUNT = 368345;
const size_t ITEM_COUNT = 50000;
const size_t LOOP_COUNT = 1000;


void disp_msg(const std::string &msg)
{
    std::cout << "Testing " << msg << std::endl;
}

void disp_time(double time)
{
    std::cout << "Total time: " << time << "s" << std::endl;
    std::cout << "Average time: " << time / LOOP_COUNT
        << "s" << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    timer t;

    /* STL std::vector *
    disp_msg("std::vector<std::string>");
    std::vector<std::string> test_std_vector;
    test_std_vector.reserve(ITEM_COUNT);
    double total_std_vector = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_vector.insert(test_std_vector.end(),
                std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_vector.erase(test_std_vector.end() - 1);
        }
        total_std_vector += t.elapsed();
    }
    test_std_vector.shrink_to_fit();
    disp_time(total_std_vector);
    /**/

    /* STL std::list *
    disp_msg("std::list<std::string>");
    std::list<std::string> test_std_list;
    double total_std_list = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_list.push_back(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_list.pop_front();
        }
        total_std_list += t.elapsed();
    }
    disp_time(total_std_list);
    /**/

    /** DSA array_list *
    disp_msg("DSA::array_list<std::string>");
    array_list<std::string> test_array_list;
    double total_array_list = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_list.add(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_list.remove(0);
        }
        total_array_list += t.elapsed();
    }
    disp_time(total_array_list);
    /**/

    /** DSA s_linked_list *
    disp_msg("DSA::s_linked_list<string>");
    s_linked_list<string> test_linked_list;
    double total_linked_list = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_list.add(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_list.remove(0);
        }
        total_linked_list += t.elapsed();
    }
    disp_time(total_linked_list);
    /**/

    /** std::stack *
    disp_msg("std::stack<string>");
    std::stack<string> test_std_stack;
    double total_std_stack = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_stack.push(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_stack.pop();
        }
        total_std_stack += t.elapsed();
    }
    disp_time(total_std_stack);

    /* DSA array_stack *
    disp_msg("DSA::array_stack<string>");
    array_stack<string> test_array_stack;
    double total_array_stack = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_stack.push(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_stack.pop();
        }
        total_array_stack += t.elapsed();
    }
    disp_time(total_array_stack);
    /**/

    /* DSA linked_stack *
    disp_msg("DSA::linked_stack<string>");
    linked_stack<string> test_linked_stack;
    double total_linked_stack = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_stack.push(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_stack.pop();
        }
        total_linked_stack += t.elapsed();
    }
    disp_time(total_linked_stack);
    /**/

    /* STL std::queue *
    disp_msg("std::queue<string>");
    std::queue<string> test_std_queue;
    double total_std_queue = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_queue.push(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_std_queue.pop();
        }
        total_std_queue += t.elapsed();
    }
    disp_time(total_std_queue);
    /**/

    /* DSA array_queue *
    disp_msg("DSA::array_queue<string>");
    array_queue<string> test_array_queue;
    double total_array_queue = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_queue.enqueue(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_array_queue.dequeue();
        }
        total_array_queue += t.elapsed();
    }
    disp_time(total_array_queue);
    /**/

    /* DSA linked_queue *
    disp_msg("DSA::linked_queue<string>");
    linked_queue<string> test_linked_queue;
    double total_linked_queue = 0;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_queue.enqueue(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_linked_queue.dequeue();
        }
        total_linked_queue += t.elapsed();
    }
    disp_time(total_linked_queue);

    /**/

    /* DSA linked_queue */
    // N^2 = 7.96s where N = 10000
    disp_msg("DSA::dynamic_array_container<string>");
    dynamic_array_container<string> test_dac;
    double total_dac = 0;
    test_dac.reserve(ITEM_COUNT);
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        t.reset();
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_dac.push_back(std::to_string(i));
        }
        for (size_t i = 0; i < ITEM_COUNT; i++)
        {
            test_dac.remove(test_dac.size() - 1);
        }
        total_dac += t.elapsed();
    }
    test_dac.clear();
    test_dac.shrink();
    disp_time(total_dac);

    /**/

#ifdef __linux__
    std::cout << "Press enter to continue...";
    std::cin.get();
#elif _WIN32
    system("pause");
#endif
    return 0;
}
