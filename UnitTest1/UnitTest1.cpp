#include "pch.h"
#include "CppUnitTest.h"
#include "../TaskEight/TaskEight.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1) //проверка на оператор сложения
		{
			map<int, int> temp_map1 = { {3, 1}, {2, 0}, {1, 1}, {0, 4} };
			Multinomial multi1(temp_map1, 3);
			map<int, int> temp_map2 = { {3, 1}, {2, 0}, {1, 1}, {0, 4} };
			Multinomial multi2(temp_map2, 3);
			Multinomial multi_result = multi1 + multi2;
			Assert::AreEqual(multi_result.MaxPower(), 3);
			Assert::AreEqual(multi_result.Coeff(3), 2);
			Assert::AreEqual(multi_result.Coeff(2), 0);
			Assert::AreEqual(multi_result.Coeff(1), 2);
			Assert::AreEqual(multi_result.Coeff(0), 8);
		}

		TEST_METHOD(TestMethod2) //проверка на оператор разности
		{
			map<int, int> temp_map1 = { {3, 1}, {2, 0}, {1, 1}, {0, 4} };
			Multinomial multi1(temp_map1, 3);
			map<int, int> temp_map2 = { {3, 1}, {2, 0}, {1, 1}, {0, 4} };
			Multinomial multi2(temp_map2, 3);
			Multinomial multi_result = multi1 - multi2;
			Assert::AreEqual(multi_result.MaxPower(), 0);
			Assert::AreEqual(multi_result.Coeff(3), 0);
			Assert::AreEqual(multi_result.Coeff(2), 0);
			Assert::AreEqual(multi_result.Coeff(1), 0);
			Assert::AreEqual(multi_result.Coeff(0), 0);
		}

		TEST_METHOD(TestMethod3) //проверка на оператор умножения
		{
			map<int, int> temp_map1 = { {1, 2}, {0, 3} };
			Multinomial multi1(temp_map1, 1);
			map<int, int> temp_map2 = { {1, 5}, {0, 0} };
			Multinomial multi2(temp_map2, 1);
			Multinomial multi_result = multi1 * multi2;
			Assert::AreEqual(multi_result.MaxPower(), 2);
			Assert::AreEqual(multi_result.Coeff(2), 10);
			Assert::AreEqual(multi_result.Coeff(1), 15);
			Assert::AreEqual(multi_result.Coeff(0), 0);
		}
	};
}
