#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/fixed_set.h"

using std::to_string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(fixed_set_test)
    {
        TEST_METHOD(test_constructor)
        {
            fixed_set<string, 100> test_set1;
            Assert::IsTrue(test_set1.empty());
            Assert::IsFalse(test_set1.full());
            Assert::AreEqual((size_t)0, test_set1.size());
            Assert::AreEqual((size_t)100, test_set1.capacity());

            for (size_t i = 0; i < 80; ++i)
            {
                test_set1.add(to_string(i));
            }

            fixed_set<string, 100> test_set2(test_set1);
            Assert::IsFalse(test_set1.empty());
            Assert::IsFalse(test_set1.full());
            Assert::AreEqual((size_t)80, test_set1.size());
            Assert::AreEqual((size_t)100, test_set1.capacity());
            Assert::IsFalse(test_set2.empty());
            Assert::IsFalse(test_set2.full());
            Assert::AreEqual((size_t)80, test_set2.size());
            Assert::AreEqual((size_t)100, test_set2.capacity());

            fixed_set<string, 100> test_set3(std::move(test_set2));
            Assert::IsFalse(test_set1.empty());
            Assert::IsFalse(test_set1.full());
            Assert::AreEqual((size_t)80, test_set1.size());
            Assert::AreEqual((size_t)100, test_set1.capacity());
            Assert::IsFalse(test_set3.empty());
            Assert::IsFalse(test_set3.full());
            Assert::AreEqual((size_t)80, test_set3.size());
            Assert::AreEqual((size_t)100, test_set3.capacity());

            test_set3.clear();
            Assert::IsFalse(test_set1.empty());
            Assert::IsFalse(test_set1.full());
            Assert::AreEqual((size_t)80, test_set1.size());
            Assert::AreEqual((size_t)100, test_set1.capacity());
            Assert::IsTrue(test_set3.empty());
            Assert::IsFalse(test_set3.full());
            Assert::AreEqual((size_t)0, test_set3.size());
            Assert::AreEqual((size_t)100, test_set3.capacity());
        }

        TEST_METHOD(test_size)
        {
            fixed_set<string, 100> test_set;
            Assert::AreEqual((size_t)0, test_set.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
                Assert::AreEqual(i + 1, test_set.size());
            }
            for (size_t i = 0; i < 100; i++)
            {
                test_set.remove();
                Assert::AreEqual(99 - i, test_set.size());
            }
        }

        TEST_METHOD(test_empty)
        {
            fixed_set<string, 100> test_set;
            Assert::IsTrue(test_set.empty());
            Assert::AreEqual((size_t)0, test_set.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
                Assert::IsFalse(test_set.empty());
            }
            test_set.clear();
            Assert::IsTrue(test_set.empty());
        }

        TEST_METHOD(test_full)
        {
            fixed_set<string, 100> test_set;
            Assert::AreEqual((size_t)0, test_set.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::IsFalse(test_set.full());
                test_set.add(to_string(i));
            }
            Assert::IsTrue(test_set.full());
            test_set.remove();
            Assert::IsFalse(test_set.full());
            test_set.clear();
            Assert::IsFalse(test_set.full());
        }

        TEST_METHOD(test_clear)
        {
            fixed_set<string, 100> test_set;
            Assert::IsTrue(test_set.empty());
            Assert::IsFalse(test_set.full());
            Assert::AreEqual((size_t)0, test_set.size());
            Assert::AreEqual((size_t)100, test_set.capacity());
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
            }
            Assert::IsFalse(test_set.empty());
            Assert::IsTrue(test_set.full());
            Assert::AreEqual((size_t)100, test_set.size());
            Assert::AreEqual((size_t)100, test_set.capacity());
            test_set.clear();
            Assert::IsTrue(test_set.empty());
            Assert::IsFalse(test_set.full());
            Assert::AreEqual((size_t)0, test_set.size());
            Assert::AreEqual((size_t)100, test_set.capacity());
        }

        TEST_METHOD(test_add)
        {
            fixed_set<string, 100> test_set;
            Assert::AreEqual((size_t)0, test_set.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
                Assert::IsTrue(test_set.contains(to_string(i)));
                Assert::AreEqual(i + 1, test_set.size());
                if (!test_set.full())
                {
                    Assert::ExpectException<duplicate_element>
                        ([&test_set, &i]
                    {
                        (&test_set)->add(to_string(i));
                    });
                }
            }
            Assert::ExpectException<full_container>([&test_set]
            {
                (&test_set)->add("String");
            });
        }

        TEST_METHOD(test_remove)
        {
            fixed_set<string, 100> test_set;
            Assert::AreEqual((size_t)0, test_set.size());

            // remove()
            // Test exception.
            Assert::ExpectException<empty_container>([&test_set]
            {
                (&test_set)->remove();
            });

            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
            }
            Assert::AreEqual((size_t)100, test_set.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(99 - i), 
                    test_set.remove());
                Assert::IsFalse(test_set.contains(to_string(99 - i)));
                Assert::AreEqual(99 - i, test_set.size());
            }
            Assert::ExpectException<empty_container>([&test_set]
            {
                (&test_set)->remove();
            });

            // remove(const size_t &num)
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
            }
            Assert::AreEqual((size_t)100, test_set.size());

            string *removed = test_set.remove(0);
            Assert::IsNull(removed);
            removed = test_set.remove(80);
            Assert::AreEqual((size_t)20, test_set.size());
            for (size_t i = 0; i < 80; i++)
            {
                Assert::AreEqual(to_string(i + 20), removed[i]);
                Assert::IsFalse(test_set.contains(to_string(i + 20)));
            }
            delete[] removed;

            Assert::ExpectException<illegal_argument>([&test_set]
            {
                (&test_set)->remove(21);
            });

            // remove(const T &entry)
            test_set.clear();
            for (size_t i = 0; i < 100; i++)
            {
                test_set.add(to_string(i));
            }
            Assert::AreEqual((size_t)100, test_set.size());
            Assert::ExpectException<no_such_element>([&test_set]
            {
                (&test_set)->remove("String");
            });
            for (size_t i = 0; i < 100; i++)
            {
                test_set.remove(to_string(i));
                Assert::IsFalse(test_set.contains(to_string(i)));
                Assert::AreEqual(99 - i, test_set.size());
            }
        }

        TEST_METHOD(test_assignment_operator)
        {

        }
    };
}