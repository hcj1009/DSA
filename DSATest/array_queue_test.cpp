#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "../DSA/array_queue.h"

using namespace std;
using namespace DSA;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{
    TEST_CLASS(array_queue_test)
    {
        TEST_METHOD(test_constructor)
        {
            // Default constructor.
            array_queue<string> test_queue1;

            // Default constructor (specified BASE_CAPACITY).
            array_queue<string> test_queue2(50);


            Assert::IsTrue(test_queue1.empty());
            Assert::AreEqual((size_t)0, test_queue1.size());
            Assert::AreEqual((size_t)10, test_queue1.capacity());

            Assert::IsTrue(test_queue1.empty());
            Assert::AreEqual((size_t)0, test_queue2.size());
            Assert::AreEqual((size_t)50, test_queue2.capacity());


            // TODO Enqueue to test_queue1 & 2
            /**
            array_queue<string> test_queue3(test_queue1);
            array_queue<string> test_queue4(test_queue1);


            Assert::IsTrue(test_queue3.empty());
            Assert::AreEqual((size_t)0, test_queue3.size());
            Assert::AreEqual((size_t)10, test_queue3.capacity());

            Assert::IsTrue(test_queue4.empty());
            Assert::AreEqual((size_t)0, test_queue4.size());
            Assert::AreEqual((size_t)50, test_queue4.capacity());

            array_queue<string> test_queue5(move(test_queue1));
            array_queue<string> test_queue6(move(test_queue2));

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
            array_queue<string> test_queue;

            Assert::IsTrue(test_queue.empty());
            test_queue.enqueue("String");
            Assert::IsFalse(test_queue.empty());
        }

        TEST_METHOD(test_size)
        {
            array_queue<string> test_queue;
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

        TEST_METHOD(test_capacity)
        {
            array_queue<string> test_queue1;
            Assert::AreEqual((size_t)0, test_queue1.size());
            Assert::AreEqual((size_t)10, test_queue1.capacity());

            array_queue<string> test_queue2(50);
            Assert::AreEqual((size_t)0, test_queue2.size());
            Assert::AreEqual((size_t)50, test_queue2.capacity());

            for (size_t i = 0; i < 50; i++)
            {
                test_queue1.enqueue("String " + to_string(i));
                test_queue2.enqueue("String " + to_string(i));
            }

            Assert::AreEqual((size_t)50, test_queue1.size());
            Assert::AreEqual((size_t)80, test_queue1.capacity());
            Assert::AreEqual((size_t)50, test_queue2.size());
            Assert::AreEqual((size_t)50, test_queue2.capacity());

            for (size_t i = 0; i < 20; i++)
            {
                test_queue1.dequeue();
                test_queue2.dequeue();
            }

            Assert::AreEqual((size_t)30, test_queue1.size());
            Assert::AreEqual((size_t)80, test_queue1.capacity());
            Assert::AreEqual((size_t)30, test_queue2.size());
            Assert::AreEqual((size_t)50, test_queue2.capacity());

            for (size_t i = 0; i < 70; i++)
            {
                test_queue1.enqueue("String " + to_string(i));
                test_queue2.enqueue("String " + to_string(i));
            }

            Assert::AreEqual((size_t)100, test_queue1.size());
            Assert::AreEqual((size_t)160, test_queue1.capacity());
            Assert::AreEqual((size_t)100, test_queue2.size());
            Assert::AreEqual((size_t)100, test_queue2.capacity());
        }

        TEST_METHOD(test_front)
        {
            array_queue<string> test_queue;
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
            array_queue<string> test_queue;
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
            array_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::AreEqual((size_t)0, test_queue.size());
            for (size_t i = 0; i < 100; i++)
            {
                test_queue.enqueue("String" + to_string(i));
            }
            Assert::IsFalse(test_queue.empty());
            Assert::AreEqual((size_t)100, test_queue.size());
            Assert::AreEqual((size_t)160, test_queue.capacity());
            test_queue.clear();
            Assert::IsTrue(test_queue.empty());
            Assert::AreEqual((size_t)0, test_queue.size());
            Assert::AreEqual((size_t)10, test_queue.capacity());
        }

        TEST_METHOD(test_contains)
        {
            // TODO Test contains(const T &entry)
            /*
            array_queue<string> test_queue;
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
            array_queue<string> test_queue;
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
            array_queue<string> test_queue;
            Assert::IsTrue(test_queue.empty());
            Assert::ExpectException<empty_container>([&test_queue]
            {
                (&test_queue)->dequeue();
            });
            */
        }
    };
}