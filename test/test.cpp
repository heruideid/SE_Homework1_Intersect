#include "pch.h"
#include "CppUnitTest.h"
#include "../Intersect/obj.h"
#include "../Intersect/obj.cpp"
#include <set>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			set<Point> points;
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back({ 1,3,4,2 });
			lines.push_back({ 10,7,9,8 });
			circles.push_back({5,5,5});
			circles.push_back({2,0,3});
			int lines_size = lines.size();
			int circles_size = circles.size();
		
			for (int i = 0; i < lines_size; i++) {
				for (int j = i + 1; j < lines_size; j++) {
					lines.at(i).getIntersectPoint(&points, lines.at(j));
				}
			}

			for (int i = 0; i < lines_size; i++) {
				for (int j = 0; j < circles_size; j++) {
					lines.at(i).getIntersectPoint(&points, circles.at(j));
				}
			}

			for (int i = 0; i < circles_size; i++) {
				for (int j = i + 1; j < circles_size; j++) {
					circles.at(i).getIntersectPoint(&points, circles.at(j));
				}
			}
			Assert::AreEqual((int)points.size(),9);
		}
		TEST_METHOD(TestMethod2)
		{
			set<Point> points;
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back({ 0,7,1,7 }); //y=7
			lines.push_back({ 0,0,0,1000 });//x=0
			lines.push_back({ 3,0,3,-1000 });//x=3
			lines.push_back({ 0,0,3,4 });//y=4*x/3
			circles.push_back({ 0,0,2 });
			circles.push_back({ 3,4,3 });
			circles.push_back({ 4.5,4,2.25 });
			int lines_size = lines.size();
			int circles_size = circles.size();

			for (int i = 0; i < lines_size; i++) {
				for (int j = i + 1; j < lines_size; j++) {
					lines.at(i).getIntersectPoint(&points, lines.at(j));
				}
			}

			for (int i = 0; i < lines_size; i++) {
				for (int j = 0; j < circles_size; j++) {
					lines.at(i).getIntersectPoint(&points, circles.at(j));
				}
			}

			for (int i = 0; i < circles_size; i++) {
				for (int j = i + 1; j < circles_size; j++) {
					circles.at(i).getIntersectPoint(&points, circles.at(j));
				}
			}
			for (auto p:points) {
				cout << p.x << " " << p.y << endl;
			}
			Assert::AreEqual((int)points.size(), 14);
		}
	};
}
