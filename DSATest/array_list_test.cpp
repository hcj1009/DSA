#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/array_list.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(array_list_test)
    {
    public:
        TEST_METHOD(test_constructor)
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

            Assert::AreEqual((size_t) 0, test_list1.size());
            Assert::AreEqual((size_t) 10, test_list1.capacity());

            Assert::AreEqual((size_t) 100, test_list2.size());
            Assert::AreEqual((size_t) 160, test_list2.capacity());

            Assert::AreEqual((size_t) 0, test_list3.size());
            Assert::AreEqual((size_t) 50, test_list3.capacity());

            Assert::AreEqual((size_t) 100, test_list4.size());
            Assert::AreEqual((size_t) 100, test_list4.capacity());

            Assert::AreEqual((size_t) 100, test_list5.size());
            Assert::AreEqual((size_t) 160, test_list5.capacity());

            Assert::AreEqual((size_t) 100, test_list6.size());
            Assert::AreEqual((size_t) 100, test_list6.capacity());
        }

        TEST_METHOD(test_empty)
        {
            array_list<string> test_list;

            Assert::IsTrue(test_list.empty());
            test_list.add("List");
            Assert::IsFalse(test_list.empty());
        }

        TEST_METHOD(test_size)
        {
            array_list<string> test_list;
            Assert::AreEqual((size_t) 0, test_list.size());
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual((size_t) (i + 1), test_list.size());
            }
            for (int i = 99; i >= 0; i--)
            {
                test_list.remove(i);
                Assert::AreEqual((size_t) i, test_list.size());
            }
        }

        TEST_METHOD(test_capacity)
        {
            array_list<string> test_list1;
            array_list<string, 50> test_list2;
            Assert::AreEqual((size_t) 10, test_list1.capacity());
            Assert::AreEqual((size_t) 50, test_list2.capacity());
            for (int i = 0; i < 250; i++)
            {
                test_list1.add("String " + to_string(i));
                test_list2.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 320, test_list1.capacity());
            Assert::AreEqual((size_t) 400, test_list2.capacity());
        }

        TEST_METHOD(test_clear)
        {
            array_list<string> test_list;
            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)10, test_list.capacity());
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)100, test_list.size());
            Assert::AreEqual((size_t)160, test_list.capacity());

            test_list.clear();

            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)0, test_list.size());
            Assert::AreEqual((size_t)10, test_list.capacity());
        }

        TEST_METHOD(test_index_of)
        {
            array_list<string> test_list;
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 100, test_list.size());
        }

        TEST_METHOD(test_contains)
        {
            array_list<string> test_list;
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 100, test_list.size());
            for (int i = 0; i < 100; i++)
            {
                Assert::IsTrue(test_list.contains("String " + to_string(i)));
            }
            Assert::IsFalse(test_list.contains(""));
            Assert::IsFalse(test_list.contains("String"));
        }

        TEST_METHOD(test_get)
        {
            array_list<string> test_list;
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 100, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual((string) ("String " + to_string(i)),
                    test_list.get(i));
            }
        }

        TEST_METHOD(test_set)
        {
            array_list<string> test_list;
            for (int i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 100, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_list.set(99 - i, "String " + to_string(i));
                Assert::AreEqual((string) ("String " + to_string(i)), 
                    test_list.get(99 - i));
            }
        }

        TEST_METHOD(test_add)
        {
            array_list<string> test_list;
            Assert::AreEqual((size_t) 0, test_list.size());
            for (int i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual((size_t) (i + 1), test_list.size());
                Assert::AreEqual((string) ("String " + to_string(i)), test_list.get(i));
            }
            test_list.add(0, "front");
            Assert::AreEqual((size_t) 11, test_list.size());
            Assert::AreEqual((string) "front", test_list.get(0));
            Assert::AreEqual((string) "String 0", test_list.get(1));
            test_list.add(1, "first");
            Assert::AreEqual((size_t) 12, test_list.size());
            Assert::AreEqual((string) "front", test_list.get(0));
            Assert::AreEqual((string) "first", test_list.get(1));
            Assert::AreEqual((string) "String 0", test_list.get(2));
            test_list.add(6, "middle");
            Assert::AreEqual((size_t) 13, test_list.size());
            Assert::AreEqual((string) "String 3", test_list.get(5));
            Assert::AreEqual((string) "middle", test_list.get(6));
            Assert::AreEqual((string) "String 4", test_list.get(7));
            test_list.add(13, "end");
            Assert::AreEqual((size_t) 14, test_list.size());
            Assert::AreEqual((string) "String 9", test_list.get(12));
            Assert::AreEqual((string) "end", test_list.get(13));
            test_list.add(13, "last");
            Assert::AreEqual((size_t) 15, test_list.size());
            Assert::AreEqual((string) "String 9", test_list.get(12));
            Assert::AreEqual((string) "last", test_list.get(13));
            Assert::AreEqual((string) "end", test_list.get(14));
        }

        TEST_METHOD(test_remove)
        {
            array_list<string> test_list;

            // Testing remove(const size_t & index)
            for (int i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 10, test_list.size());

            test_list.remove(0);
            Assert::AreEqual((size_t) 9, test_list.size());
            Assert::IsFalse(test_list.contains("String 0"));
            Assert::AreEqual((string) "String 1", test_list.get(0));
            Assert::AreEqual((string) "String 2", test_list.get(1));
            test_list.remove(8);
            Assert::AreEqual((size_t) 8, test_list.size());
            Assert::IsFalse(test_list.contains("String 9"));
            Assert::AreEqual((string) "String 7", test_list.get(6));
            Assert::AreEqual((string) "String 8", test_list.get(7));
            test_list.remove(4);
            Assert::AreEqual((size_t) 7, test_list.size());
            Assert::IsFalse(test_list.contains("String 5"));
            Assert::AreEqual((string) "String 4", test_list.get(3));
            Assert::AreEqual((string) "String 6", test_list.get(4));
            Assert::AreEqual((string) "String 7", test_list.get(5));

            test_list.clear();
            // Testing remove(const T & element)
            for (int i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t) 10, test_list.size());

            test_list.remove("String 0");
            Assert::AreEqual((size_t) 9, test_list.size());
            Assert::IsFalse(test_list.contains("String 0"));
            Assert::AreEqual((string) "String 1", test_list.get(0));
            Assert::AreEqual((string) "String 2", test_list.get(1));
            test_list.remove("String 9");
            Assert::AreEqual((size_t) 8, test_list.size());
            Assert::IsFalse(test_list.contains("String 9"));
            Assert::AreEqual((string) "String 7", test_list.get(6));
            Assert::AreEqual((string) "String 8", test_list.get(7));
            test_list.remove("String 5");
            Assert::AreEqual((size_t) 7, test_list.size());
            Assert::IsFalse(test_list.contains("String 5"));
            Assert::AreEqual((string) "String 4", test_list.get(3));
            Assert::AreEqual((string) "String 6", test_list.get(4));
            Assert::AreEqual((string) "String 7", test_list.get(5));
        }
    };
}