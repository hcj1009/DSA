#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/linked_queue.h"

using namespace std;
using namespace DSA;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(linked_queue_test) 
    {
        TEST_METHOD(test_constructor)
        {
            // Default constructor.
            linked_queue<string> test_queue1;

            Assert::IsTrue(test_queue1.empty());
            Assert::AreEqual((size_t)0, test_queue1.size());

            // TODO Enqueue to test_queue1 & 2
            /**
            linked_queue<string> test_queue3(test_queue1);
            linked_queue<string> test_queue4(test_queue1);


            Assert::IsTrue(test_queue3.empty());
            Assert::AreEqual((size_t)0, test_queue3.size());
            Assert::AreEqual((size_t)10, test_queue3.capacity());

            Assert::IsTrue(test_queue4.empty());
            Assert::AreEqual((size_t)0, test_queue4.size());
            Assert::AreEqual((size_t)50, test_queue4.capacity());

            linked_queue<string> test_queue5(move(test_queue1));
            linked_queue<string> test_queue6(move(test_queue2));

            Assert::IsTrue(test_queue5.empty());
            Assert::AreEqual((size_t)0, test_queue5.size());
            Assert::AreEqual((size_t)10, test_queue5.capacity());

            Assert::IsTrue(test_queue6.empty());
            Assert::AreEqual((size_t)0, test_queue6.size());
            Assert::AreEqual((size_t)50, test_queue6.capacity());
            /**/
        }

        TEST_METHOD(test_empty)
        {
            linked_queue<string> test_queue;

            Assert::IsTrue(test_queue.empty());
            test_queue.enqueue("String");
            Assert::IsFalse(test_queue.empty());
        }

        TEST_METHOD(test_size)
        {
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::AreEqual((size_t)0, test_queue.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_queue.enqueue("String " + to_string(i));
                Assert::AreEqual(i + 1, test_queue.size());
            }

            test_queue.front();
            test_queue.back();
            Assert::AreEqual((size_t)100, test_queue.size());

            for (size_t i = 0; i < 100; i++)
            {
                test_queue.dequeue();
                Assert::AreEqual(99 - i, test_queue.size());
            }
        }

        TEST_METHOD(test_front)
        {
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::ExpectException<empty_container>([&test_queue]
            {
                (&test_queue)->front();
            });

            for (size_t i = 0; i < 100; i++)
            {
                test_queue.enqueue("String " + to_string(i));
                Assert::AreEqual((string)"String 0",
                    test_queue.front());
            }
            Assert::AreEqual((size_t)100, test_queue.size());
            for (size_t i = 0; i < 99; i++)
            {
                Assert::AreEqual("String " + to_string(i),
                    test_queue.front());
                test_queue.dequeue();
            }
            Assert::AreEqual((string)"String 99",
                test_queue.front());
        }

        TEST_METHOD(test_back)
        {
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::ExpectException<empty_container>([&test_queue]
            {
                (&test_queue)->back();
            });

            for (size_t i = 0; i < 100; i++)
            {
                test_queue.enqueue("String " + to_string(i));

                Assert::AreEqual("String " + to_string(i),
                    test_queue.back());
            }
            Assert::AreEqual((size_t)100, test_queue.size());
            for (size_t i = 0; i < 99; i++)
            {
                Assert::AreEqual((string)"String 99",
                    test_queue.back());
                test_queue.dequeue();
            }
            Assert::AreEqual((string)"String 99",
                test_queue.back());
        }

        TEST_METHOD(test_clear)
        {
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::AreEqual((size_t)0, test_queue.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_queue.enqueue("String" + to_string(i));
            }
            Assert::IsFalse(test_queue.empty());
            Assert::AreEqual((size_t)100, test_queue.size());
            test_queue.clear();
            Assert::IsTrue(test_queue.empty());
            Assert::AreEqual((size_t)0, test_queue.size());
        }

        TEST_METHOD(test_contains)
        {
            // TODO Test contains(const T &entry)
            /*
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::IsFalse(test_queue.contains(""));
            Assert::IsFalse(test_queue.contains("String"));
            for (size_t i = 0; i < 100; i++)
            {
            test_queue.enqueue("String " + to_string(i));
            }
            Assert::AreEqual((size_t)100, test_queue.size());
            for (size_t i = 0; i < 100; i++)
            {
            Assert::IsTrue(test_queue.contains("String " + to_string(i)));
            }
            Assert::IsFalse(test_queue.contains(""));
            Assert::IsFalse(test_queue.contains("String"));
            for (size_t i = 0; i < 100; i++)
            {
            test_queue.dequeue();
            Assert::IsFalse(test_queue.contains("String"
            + to_string(i)));
            }
            */
        }

        TEST_METHOD(test_enqueue)
        {
            // TODO Test enqueue(const T &entry)
            /*
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());

            for (size_t i = 0; i < 100; i++)
            {
            test_queue.enqueue("String " + to_string(i));
            Assert::AreEqual((string)"String 0", test_queue.front());
            Assert::AreEqual("String " + to_string(i), test_queue.back());
            }
            */
        }

        TEST_METHOD(test_dequeue)
        {
            // TODO Test dequeue()
            /*
            linked_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::ExpectException<empty_container>([&test_queue]
            {
            (&test_queue)->dequeue();
            });
            */
        }
    };
}