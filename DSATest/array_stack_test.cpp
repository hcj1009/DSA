#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/array_stack.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(array_stack_test)
    {
    public:
        TEST_METHOD(test_constructor)
        {
            // Default constructor.
            array_stack<string> test_stack1;

            // Default constructor (specified BASE_CAPACITY).
            array_stack<string, 50> test_stack2;

            Assert::AreEqual((size_t)0, test_stack1.size());
            Assert::AreEqual((size_t)10, test_stack1.capacity());

            Assert::AreEqual((size_t)0, test_stack2.size());
            Assert::AreEqual((size_t)50, test_stack2.capacity());
        }

        TEST_METHOD(test_empty)
        {
            array_stack<string> test_stack;

            Assert::IsTrue(test_stack.empty());
            test_stack.push("String");
            Assert::IsFalse(test_stack.empty());
        }

        TEST_METHOD(test_size)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());
            Assert::AreEqual((size_t)0, test_stack.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
                Assert::AreEqual(i + 1, test_stack.size());
            }

            test_stack.peek();
            Assert::AreEqual((size_t)100, test_stack.size());

            for (size_t i = 0; i < 100; i++)
            {
                test_stack.pop();
                Assert::AreEqual(99 - i, test_stack.size());
            }
        }

        TEST_METHOD(test_capacity)
        {
            array_stack<string> test_stack1;
            Assert::AreEqual((size_t)0, test_stack1.size());
            Assert::AreEqual((size_t)10, test_stack1.capacity());

            array_stack<string, 50> test_stack2;
            Assert::AreEqual((size_t)0, test_stack2.size());
            Assert::AreEqual((size_t)50, test_stack2.capacity());

            for (size_t i = 0; i < 100; i++)
            {
                test_stack1.push("String " + to_string(i));
                test_stack2.push("String " + to_string(i));
            }

            Assert::AreEqual((size_t)100, test_stack1.size());
            Assert::AreEqual((size_t)160, test_stack1.capacity());
            Assert::AreEqual((size_t)100, test_stack2.size());
            Assert::AreEqual((size_t)100, test_stack2.capacity());
        }

        TEST_METHOD(test_clear)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());
            Assert::AreEqual((size_t)0, test_stack.size());
            Assert::AreEqual((size_t)10, test_stack.capacity());
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
            }
            Assert::IsFalse(test_stack.empty());
            Assert::AreEqual((size_t)100, test_stack.size());
            Assert::AreEqual((size_t)160, test_stack.capacity());
            test_stack.clear();
            Assert::IsTrue(test_stack.empty());
            Assert::AreEqual((size_t)0, test_stack.size());
            Assert::AreEqual((size_t)10, test_stack.capacity());
        }

        TEST_METHOD(test_contains)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());
            Assert::IsFalse(test_stack.contains(""));
            Assert::IsFalse(test_stack.contains("String"));
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_stack.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::IsTrue(test_stack.contains("String " + to_string(i)));
            }
            Assert::IsFalse(test_stack.contains(""));
            Assert::IsFalse(test_stack.contains("String"));
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.pop();
                Assert::IsFalse(test_stack.contains("String "
                    + to_string(99 - i)));
            }
        }

        TEST_METHOD(test_push)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
                Assert::AreEqual(i + 1, test_stack.size());
                Assert::AreEqual("String " + to_string(i), test_stack.peek());
            }
        }

        TEST_METHOD(test_pop)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());

            Assert::ExpectException<empty_container>([&test_stack]
            {
                (&test_stack)->pop();
            });

            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_stack.size());
            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual("String " + to_string(99 - i),
                    test_stack.pop());
                Assert::AreEqual(99 - i, test_stack.size());
                Assert::AreEqual((size_t)160, test_stack.capacity());
            }
        }

        TEST_METHOD(test_peek)
        {
            array_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());

            Assert::ExpectException<empty_container>([&test_stack]
            {
                (&test_stack)->peek();
            });

            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
                Assert::AreEqual("String " + to_string(i), test_stack.peek());
                Assert::AreEqual(i + 1, test_stack.size());
            }
        }

        TEST_METHOD(test_assignment_operator)
        {
            array_stack<string> test_stack1;
            for (size_t i = 0; i < 100; i++)
            {
                test_stack1.push(to_string(i));
                Assert::AreEqual(to_string(i), test_stack1.peek());
            }
            Assert::AreEqual((size_t)100, test_stack1.size());

            array_stack<string> test_stack2;
            Assert::IsTrue(test_stack2.empty());
            Assert::AreEqual((size_t)0, test_stack2.size());
            Assert::AreEqual((size_t)10, test_stack2.capacity());

            test_stack2 = test_stack1;
            Assert::IsFalse(test_stack1.empty());
            Assert::AreEqual((size_t)100, test_stack1.size());
            Assert::AreEqual((size_t)160, test_stack1.capacity());
            Assert::IsFalse(test_stack2.empty());
            Assert::AreEqual((size_t)100, test_stack2.size());
            Assert::AreEqual((size_t)160, test_stack2.capacity());

            for (size_t i = 0; i < 100; i++)
            {
                Assert::AreEqual(to_string(99 - i), test_stack1.pop());
                Assert::AreEqual(to_string(99 - i), test_stack2.pop());
            }

            // Test rvalue cases.
            test_stack2.clear();
            Assert::IsTrue(test_stack2.empty());
            Assert::AreEqual((size_t)0, test_stack2.size());
            Assert::AreEqual((size_t)10, test_stack2.capacity());

            for (size_t i = 0; i < 100; i++)
            {
                test_stack1.push(to_string(i));
                Assert::AreEqual(to_string(i), test_stack1.peek());
            }
            Assert::AreEqual((size_t)100, test_stack1.size());

            test_stack2 = move(test_stack1);
            Assert::IsTrue(test_stack1.empty());
            Assert::AreEqual((size_t)0, test_stack1.size());
            Assert::AreEqual((size_t)160, test_stack1.capacity());
            Assert::IsFalse(test_stack2.empty());
            Assert::AreEqual((size_t)100, test_stack2.size());
            Assert::AreEqual((size_t)160, test_stack2.capacity());
        }
    };
}