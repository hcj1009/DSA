#include "stdafx.h"
#include "CppUnitTest.h"

#include <exception>
#include "../DSA/array_bag.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSATest
{        
    TEST_CLASS(array_bag_test)
    {
    public:
        TEST_METHOD(test_empty)
        {
            array_bag<int> testBag;
            Assert::IsTrue(testBag.empty());
            testBag.add(12);
            Assert::IsFalse(testBag.empty());
            testBag.remove();
            Assert::IsTrue(testBag.empty());
        }

        TEST_METHOD(test_size)
        {
            array_bag<int> testBag;
            Assert::AreEqual((size_t) 0, testBag.size());
            for (int i = 0; i < 50; i++)
            {
                testBag.add(i);
                Assert::AreEqual((size_t) i + 1, testBag.size());
            }
            for (int i = 0; i < 50; i++)
            {
                testBag.remove();
                Assert::AreEqual((size_t) 49 - i, testBag.size());
            }
            Assert::AreEqual((size_t) 0, testBag.size());
        }

        TEST_METHOD(test_capacity)
        {
            array_bag<int> testBag1;
            array_bag<int, 20> testBag2;
            Assert::AreEqual((size_t) 10, testBag1.capacity());
            Assert::AreEqual((size_t) 20, testBag2.capacity());
            for (int i = 0; i < 15; i++)
            {
                testBag1.add(i);
                testBag2.add(i);
            }
            Assert::AreEqual((size_t) 20, testBag1.capacity());
            Assert::AreEqual((size_t) 20, testBag2.capacity());
            for (int i = 0; i < 15; i++)
            {
                testBag1.add(i);
                testBag2.add(i);
            }
            Assert::AreEqual((size_t) 40, testBag1.capacity());
            Assert::AreEqual((size_t) 40, testBag2.capacity());
        }

        TEST_METHOD(test_add)
        {
            array_bag<int> testBag;
            for (int i = 0; i < 50; i++)
            {
                testBag.add(i);
                Assert::AreEqual((size_t) i + 1, testBag.size());
                Assert::IsTrue(testBag.contains(i));
                Assert::AreEqual((size_t) 1, testBag.count(i));
            }
        }

        TEST_METHOD(test_remove)
        {
            array_bag<int> testBag;
            for (int i = 0; i < 50; i++)
            {
                testBag.add(i);
            }
            for (int i = 49; i >= 0; i--)
            {
                Assert::AreEqual(i, testBag.remove());
                Assert::AreEqual((size_t) i, testBag.size());
                Assert::IsFalse(testBag.contains(i));
                Assert::AreEqual((size_t) 0, testBag.count(i));
            }
            Assert::IsTrue(testBag.empty());

            //auto func = [&testBag] { (&testBag)->remove(12); };
            //Assert::ExpectException<no_such_element>(func);

            for (int i = 0; i < 50; i++)
            {
                testBag.add(i);
            }
            for (int i = 0; i < 50; i++)
            {
                testBag.remove(i);
                Assert::AreEqual((size_t) 49 - i, testBag.size());
                Assert::IsFalse(testBag.contains(i));
                Assert::AreEqual((size_t) 0, testBag.count(i));
            }
        }
    };
}