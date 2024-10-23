#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_07.3_rec/lab_07.3_rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest073it
{
	TEST_CLASS(UnitTest073it)
	{
	public:
		static const int size = 5;
		int a[size][size] = {
				{1, 2, 2, 1, -3},
				{0, 3, -5,-7,3},
				{8, 0, 5, 4, -6},
				{-5,2, -1,7, 0},
				{1, 4, 8, 8, 9}
		};
		TEST_METHOD(TestMethod1)
		{

			int** arr = new int* [size];
			for (int i = 0; i != size; i++) {
				arr[i] = new int[size];
			}
			int expected[size] = { 5, 0, 6, 7, 3 };
			for (int i = 0; i != size; i++) {
				for (int j = 0; j != size; j++) {
					arr[i][j] = a[i][j];
				}
			}
			for (int i = 0; i != size; i++) {
				Assert::AreEqual(colSpec(arr, size, i), expected[i]);
			}

		}
		TEST_METHOD(TestMethod2) {
			int** arr = new int* [size];
			for (int i = 0; i != size; i++) {
				arr[i] = new int[size];
			}
			for (int i = 0; i != size; i++) {
				for (int j = 0; j != size; j++) {
					arr[i][j] = a[i][j];
				}
			}
			Assert::AreEqual(sumWithNegative(arr, size, size), 30);
		};
	};
}
