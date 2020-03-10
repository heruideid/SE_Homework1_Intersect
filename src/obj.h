#pragma once
#pragma once
#include<set>
using namespace std;
struct Point {
	double x, y;
	Point(double x, double y);
};

bool operator<(const Point&p1, const Point& p2);

class Circle;


class Line {
public:
	double A, B, C;//Ax+By+C=0;
	Line(double x1, double y1, double x2, double y2);
	void getIntersectPoint(set<Point>* points, Line line);
	void getIntersectPoint(set<Point>* points, Circle circle);
};

class Circle {
public:
	double cx, cy, cr;
	Circle(double x, double y, double r);
	double getCX();
	double getCY();
	double getR();
	void getIntersectPoint(set<Point>* points, Circle circle);
};

