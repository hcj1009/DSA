#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <string>
#include "../DSA/array_list.h"

using namespace std;
using namespace DSA;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(array_list_test)
    {
    public:
        TEST_METHOD(test_constructor)
        {
            string test_array[100];
            for (size_t i = 0; i < 100; i++)
            {
                test_array[i] = to_string(i);
            }

            // Default constructor.
            array_list<string> test_list1;

            // Constructor based on C array.
            array_list<string> test_list2(test_array, 100);

            // Default constructor (specified BASE_CAPACITY).
            array_list<string> test_list3(50);

            // Constructor based on C array (specified BASE_CAPACITY).
            array_list<string> test_list4(test_array, 100, 50);

            // Constructor based on List data structure.
            array_list<string> test_list5(test_list2);

            // Constructor based on List data structure
            array_list<string> test_list6(test_list4);
            array_list<string> test_list7(test_list5);

            Assert::AreEqual((size_t)0, test_list1.size());
            Assert::AreEqual((size_t)10, test_list1.capacity());

            Assert::AreEqual((size_t)100, test_list2.size());
            Assert::AreEqual((size_t)160, test_list2.capacity());

            Assert::AreEqual((size_t)0, test_list3.size());
            Assert::AreEqual((size_t)50, test_list3.capacity());

            Assert::AreEqual((size_t)100, test_list4.size());
            Assert::AreEqual((size_t)100, test_list4.capacity());

            Assert::AreEqual((size_t)100, test_list5.size());
            Assert::AreEqual((size_t)160, test_list5.capacity());

            Assert::AreEqual((size_t)100, test_list6.size());
            Assert::AreEqual((size_t)100, test_list6.capacity());

            Assert::AreEqual((size_t)100, test_list7.size());
            Assert::AreEqual((size_t)160, test_list7.capacity());

            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(i), test_list2.get(i));
                Assert::AreEqual(to_string(i), test_list4.get(i));
                Assert::AreEqual(to_string(i), test_list5.get(i));
                Assert::AreEqual(to_string(i), test_list6.get(i));
                Assert::AreEqual(to_string(i), test_list7.get(i));
            }

            array_list<string> test_list8(move(test_list5));
            Assert::AreEqual((size_t)100, test_list8.size());
            Assert::AreEqual((size_t)160, test_list8.capacity());
            Assert::AreEqual((size_t)0, test_list5.size());
            Assert::AreEqual((size_t)10, test_list5.capacity());
        }

        TEST_METHOD(test_empty)
        {
            array_list<string> test_list;

            Assert::IsTrue(test_list.empty());
            test_list.add("String");
            Assert::IsFalse(test_list.empty());
        }

        TEST_METHOD(test_size)
        {
            array_list<string> test_list;
            Assert::AreEqual((size_t)0, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual(i + 1, test_list.size());
            }
            for (size_t i = 0; i < 100; i++)
            {
                test_list.remove(99 - i);
                Assert::AreEqual(99 - i, test_list.size());
            }
        }

        TEST_METHOD(test_capacity)
        {
            array_list<string> test_list1;
            array_list<string> test_list2(50);
            Assert::AreEqual((size_t)10, test_list1.capacity());
            Assert::AreEqual((size_t)50, test_list2.capacity());
            for (size_t i = 0; i < 250; i++)
            {
                test_list1.add("String " + to_string(i));
                test_list2.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)320, test_list1.capacity());
            Assert::AreEqual((size_t)400, test_list2.capacity());
        }

        TEST_METHOD(test_clear)
        {
            array_list<string> test_list;
            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)10, test_list.capacity());
            for (size_t i = 0; i < 100; i++)
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
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());
            Assert::ExpectException<no_such_element>
            (   [&test_list]
                {
                    (&test_list)->index_of("String");
                }
            );
        }

        TEST_METHOD(test_contains)
        {
            array_list<string> test_list;
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::IsTrue(test_list.contains("String " + to_string(i)));
            }
            Assert::IsFalse(test_list.contains(""));
            Assert::IsFalse(test_list.contains("String"));
        }

        TEST_METHOD(test_get)
        {
            array_list<string> test_list;
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual((string)("String " + to_string(i)),
                    test_list.get(i));
            }
        }

        TEST_METHOD(test_set)
        {
            array_list<string> test_list;
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_list.set(99 - i, "String " + to_string(i));
                Assert::AreEqual((string)("String " + to_string(i)), 
                    test_list.get(99 - i));
            }
        }

        TEST_METHOD(test_add)
        {
            array_list<string> test_list;
            Assert::AreEqual((size_t)0, test_list.size());
            for (size_t i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual(i + 1, test_list.size());
                Assert::AreEqual((string)("String " + to_string(i)),
                    test_list.get(i));
            }
            test_list.add(0, "front");
            Assert::AreEqual((size_t)11, test_list.size());
            Assert::AreEqual((string)"front", test_list.get(0));
            Assert::AreEqual((string)"String 0", test_list.get(1));
            test_list.add(1, "first");
            Assert::AreEqual((size_t)12, test_list.size());
            Assert::AreEqual((string)"front", test_list.get(0));
            Assert::AreEqual((string)"first", test_list.get(1));
            Assert::AreEqual((string)"String 0", test_list.get(2));
            test_list.add(6, "middle");
            Assert::AreEqual((size_t)13, test_list.size());
            Assert::AreEqual((string)"String 3", test_list.get(5));
            Assert::AreEqual((string)"middle", test_list.get(6));
            Assert::AreEqual((string)"String 4", test_list.get(7));
            test_list.add(13, "end");
            Assert::AreEqual((size_t)14, test_list.size());
            Assert::AreEqual((string)"String 9", test_list.get(12));
            Assert::AreEqual((string)"end", test_list.get(13));
            test_list.add(13, "last");
            Assert::AreEqual((size_t)15, test_list.size());
            Assert::AreEqual((string)"String 9", test_list.get(12));
            Assert::AreEqual((string)"last", test_list.get(13));
            Assert::AreEqual((string)"end", test_list.get(14));
        }

        TEST_METHOD(test_remove)
        {
            array_list<string> test_list;

            // Test exceptions.
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->remove(0);
            });
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->remove(10);
            });
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->remove(-1);
            });

            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)0, test_list.size());

            for (size_t i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)10, test_list.size());

            // Case when removing the first entry from the list.
            Assert::AreEqual((string)"String 0", test_list.remove(0));
            Assert::AreEqual((size_t)9, test_list.size());
            Assert::IsFalse(test_list.contains("String 0"));
            Assert::AreEqual((string)"String 1", test_list.get(0));
            Assert::AreEqual((string)"String 2", test_list.get(1));

            // Case when removing the last entry from the list.
            Assert::AreEqual((string)"String 9", test_list.remove(8));
            Assert::AreEqual((size_t)8, test_list.size());
            Assert::IsFalse(test_list.contains("String 9"));
            Assert::AreEqual((string)"String 7", test_list.get(6));
            Assert::AreEqual((string)"String 8", test_list.get(7));

            // Other cases.
            Assert::AreEqual((string)"String 4", test_list.remove(3));
            Assert::AreEqual((size_t)7, test_list.size());
            Assert::IsFalse(test_list.contains("String 4"));
            Assert::AreEqual((string)"String 3", test_list.get(2));
            Assert::AreEqual((string)"String 5", test_list.get(3));

            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->remove(7);
            });
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->remove(-1);
            });

            // Case when removing the last entry in the list.
            test_list.clear();
            test_list.add("String");
            Assert::AreEqual((size_t)1, test_list.size());
            Assert::AreEqual((string)"String", test_list.remove(0));
            Assert::AreEqual((size_t)0, test_list.size());
            Assert::IsFalse(test_list.contains("String"));

            test_list.clear();

            // Testing remove(const T & entry)
            for (size_t i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)10, test_list.size());

            test_list.remove("String 0");
            Assert::AreEqual((size_t)9, test_list.size());
            Assert::IsFalse(test_list.contains("String 0"));
            Assert::AreEqual((string)"String 1", test_list.get(0));
            Assert::AreEqual((string)"String 2", test_list.get(1));
            test_list.remove("String 9");
            Assert::AreEqual((size_t)8, test_list.size());
            Assert::IsFalse(test_list.contains("String 9"));
            Assert::AreEqual((string)"String 7", test_list.get(6));
            Assert::AreEqual((string)"String 8", test_list.get(7));
            test_list.remove("String 5");
            Assert::AreEqual((size_t)7, test_list.size());
            Assert::IsFalse(test_list.contains("String 5"));
            Assert::AreEqual((string)"String 4", test_list.get(3));
            Assert::AreEqual((string)"String 6", test_list.get(4));
            Assert::AreEqual((string)"String 7", test_list.get(5));
        }

        TEST_METHOD(test_to_array)
        {
            array_list<string> test_list;
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add(to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());

            string *test_array = test_list.to_array();
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(i), test_array[i]);
            }
        }

        TEST_METHOD(test_assignment_operator)
        {
            array_list<string> test_list1;
            for (size_t i = 0; i < 100; i++)
            {
                test_list1.add(to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list1.size());

            // Normal cases.
            array_list<string> test_list2;
            Assert::IsTrue(test_list2.empty());
            Assert::AreEqual((size_t)0, test_list2.size());
            Assert::AreEqual((size_t)10, test_list2.capacity());

            test_list2 = test_list1;
            Assert::IsFalse(test_list1.empty());
            Assert::AreEqual((size_t)100, test_list1.size());
            Assert::AreEqual((size_t)160, test_list1.capacity());
            Assert::IsFalse(test_list2.empty());
            Assert::AreEqual((size_t)100, test_list2.size());
            Assert::AreEqual((size_t)160, test_list2.capacity());

            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(i), test_list1.get(i));
                Assert::AreEqual(to_string(i), test_list2.get(i));
            }

            // Test rvalue cases.
            // array_list<string> rvalue_list();
            // test_list2 = rvalue_list();
            test_list2.clear();
            Assert::IsTrue(test_list2.empty());
            Assert::AreEqual((size_t)0, test_list2.size());
            Assert::AreEqual((size_t)10, test_list2.capacity());

            test_list2 = move(test_list1);
            Assert::IsTrue(test_list1.empty());
            Assert::AreEqual((size_t)0, test_list1.size());
            Assert::AreEqual((size_t)160, test_list1.capacity());
            Assert::IsFalse(test_list2.empty());
            Assert::AreEqual((size_t)100, test_list2.size());
            Assert::AreEqual((size_t)160, test_list2.capacity());
        }

        TEST_METHOD(test_addition_operator)
        {
            array_list<string> test_list1;
            Assert::AreEqual((size_t)0, test_list1.size());
            for (size_t i = 0; i < 10; i++)
            {
                test_list1.add("String " + to_string(i));
                Assert::AreEqual(i + 1, test_list1.size());
                Assert::AreEqual((string)("String " + to_string(i)),
                    test_list1.get(i));
            }

            array_list<string> test_list2;
            Assert::AreEqual((size_t)0, test_list2.size());
            test_list2 = test_list1 + "String";
            Assert::AreEqual((size_t)11, test_list2.size());
            Assert::AreEqual((string)"String", test_list2.get(10));
            Assert::AreEqual((size_t)10, test_list1.size());

            test_list1 = test_list1 + "String";
            Assert::AreEqual((size_t)11, test_list1.size());
            Assert::AreEqual((string)"String", test_list1.get(10));

            test_list1 += "Another String";
            Assert::AreEqual((size_t)12, test_list1.size());
            Assert::AreEqual((string)"Another String", test_list1.get(11));
        }
    };
}