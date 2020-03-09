#include "pch.h"
#include "CppUnitTest.h"
#include "../Application1/obj.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testlineintersect
{
	TEST_CLASS(testlineintersect)
	{
	public:
		TEST_METHOD(TestMethod1)
		{	

			Line line1(0,0,1,2);
			Line line2(0, 4, 1, 6);
			Assert::AreEqual(1,2);
		}

		TEST_METHOD(TestMethod2)
		{
			Line line1(0, 0, 1, 2);
			Line line2(0, 4, 1, 6);
			Assert::AreEqual(1, 2);
		}
	};
}
