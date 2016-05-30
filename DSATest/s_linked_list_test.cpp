#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/s_linked_list.h"

using namespace std;
using namespace DSA;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(s_linked_list_test)
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
            s_linked_list<string> test_list1;

            // Constructor based on C array.
            s_linked_list<string> test_list2(test_array, 100);

            Assert::IsTrue(test_list1.empty());
            Assert::AreEqual((size_t)0, test_list1.size());

            Assert::IsFalse(test_list2.empty());
            Assert::AreEqual((size_t)100, test_list2.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(i), test_list2.get(i));
            }
        }

        TEST_METHOD(test_empty)
        {
            s_linked_list<string> test_list;

            Assert::IsTrue(test_list.empty());
            test_list.add("String");
            Assert::IsFalse(test_list.empty());
        }

        TEST_METHOD(test_size)
        {
            s_linked_list<string> test_list;
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

        TEST_METHOD(test_clear)
        {
            s_linked_list<string> test_list;
            Assert::IsTrue(test_list.empty());
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)100, test_list.size());

            test_list.clear();

            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)0, test_list.size());
        }

        TEST_METHOD(test_index_of)
        {
            s_linked_list<string> test_list;
            for (size_t i = 0; i < 100; i++)
            {
                test_list.add("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_list.size());
            Assert::ExpectException<no_such_element>
                ([&test_list]
            {
                (&test_list)->index_of("String");
            }
            );
        }

        TEST_METHOD(test_contains)
        {
            s_linked_list<string> test_list;
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
            s_linked_list<string> test_list;
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
            s_linked_list<string> test_list;
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
            s_linked_list<string> test_list;
            // Test add(const T &entry)
            Assert::IsTrue(test_list.empty());
            Assert::AreEqual((size_t)0, test_list.size());
            for (size_t i = 0; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual(i + 1, test_list.size());
                Assert::AreEqual((string)("String " + to_string(i)),
                    test_list.get(i));
            }

            test_list.clear();

            // Test add(const size_t &index, const T &entry)

            // Test exceptions in empty list.
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->add(1, "String");
            });
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->add(-1, "String");
            });

            // Case when adding to an empty list.
            test_list.add(0, "String 0");
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)1, test_list.size());
            Assert::AreEqual((string)"String 0", test_list.get(0));

            for (size_t i = 1; i < 10; i++)
            {
                test_list.add("String " + to_string(i));
                Assert::AreEqual(i + 1, test_list.size());
            }

            // Case when adding to the front.
            test_list.add(0, "front");
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)11, test_list.size());
            Assert::AreEqual((string)"front", test_list.get(0));
            Assert::AreEqual((string)"String 0", test_list.get(1));

            // Case when adding to the end.
            test_list.add(11, "end");
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)12, test_list.size());
            Assert::AreEqual((string)"String 9", test_list.get(10));
            Assert::AreEqual((string)"end", test_list.get(11));

            // Other cases.
            test_list.add(5, "middle");
            Assert::IsFalse(test_list.empty());
            Assert::AreEqual((size_t)13, test_list.size());
            Assert::AreEqual((string)"String 3", test_list.get(4));
            Assert::AreEqual((string)"middle", test_list.get(5));
            Assert::AreEqual((string)"String 4", test_list.get(6));

            // Test exceptions.
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->add(50, "String");
            });
            Assert::ExpectException<index_error>([&test_list]
            {
                (&test_list)->add(-1, "String");
            });
        }

        TEST_METHOD(test_remove)
        {
            s_linked_list<string> test_list;
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
            // Assert::IsFalse(test_list.contains("String 0"));
            Assert::AreEqual((string)"String 1", test_list.get(0));
            Assert::AreEqual((string)"String 2", test_list.get(1));

            // Case when removing the last entry from the list.
            Assert::AreEqual((string)"String 9", test_list.remove(8));
            Assert::AreEqual((size_t)8, test_list.size());
            // Assert::IsFalse(test_list.contains("String 9"));
            Assert::AreEqual((string)"String 7", test_list.get(6));
            Assert::AreEqual((string)"String 8", test_list.get(7));

            // Other cases.
            Assert::AreEqual((string)"String 4", test_list.remove(3));
            Assert::AreEqual((size_t)7, test_list.size());
            // Assert::IsFalse(test_list.contains("String 4"));
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
            // Assert::IsFalse(test_list.contains("String"));

            test_list.clear();
        }
    };
}