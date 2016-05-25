#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/linked_stack.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(linked_stack_test)
    {
    public:
        TEST_METHOD(test_constructor)
        {
            // Default constructor.
            linked_stack<string> test_stack;
            Assert::AreEqual((size_t)0, test_stack.size());
        }

        TEST_METHOD(test_empty)
        {
            linked_stack<string> test_stack;

            Assert::IsTrue(test_stack.empty());
            test_stack.push("String");
            Assert::IsFalse(test_stack.empty());
        }

        TEST_METHOD(test_size)
        {
            linked_stack<string> test_stack;
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

        TEST_METHOD(test_clear)
        {
            linked_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());
            Assert::AreEqual((size_t)0, test_stack.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_stack.push("String " + to_string(i));
            }
            Assert::IsFalse(test_stack.empty());
            Assert::AreEqual((size_t)100, test_stack.size());
            test_stack.clear();
            Assert::IsTrue(test_stack.empty());
            Assert::AreEqual((size_t)0, test_stack.size());
        }

        TEST_METHOD(test_contains)
        {
            linked_stack<string> test_stack;
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
        }

        TEST_METHOD(test_push)
        {
            linked_stack<string> test_stack;
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
            linked_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());

            Assert::ExpectException<empty_stack>([&test_stack]
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
            }
        }

        TEST_METHOD(test_peek)
        {
            linked_stack<string> test_stack;
            Assert::IsTrue(test_stack.empty());

            Assert::ExpectException<empty_stack>([&test_stack]
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
    };
}
