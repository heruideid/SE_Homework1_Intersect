#include"obj.h"
#include<set>
#include<cmath>
#include<iostream>
#define eps (1e-4)
#define equal(x,y) fabs((x)-(y))<eps
using namespace std;

bool operator<(const Point&p1, const Point& p2) {
	if (p1.x == p2.x) return p1.y < p2.y;
	return p1.x < p2.x;
}

bool operator==(const Point&p1, const Point& p2) {
	return (equal(p1.x, p2.x) && equal(p1.y,p2.y));
}

Point::Point(double x, double y){
	this->x = x;
	this->y = y;
}

Line::Line(double x1,double y1,double x2,double y2){
	A = y2 - y1;
	B = x1 - x2;
	C = x2 * y1 - x1 * y2;
}

Circle::Circle(double x, double y, double r) {
	cx = x;
	cy = y;
	this->r = r;
}

void Line::getIntersectPoint(set<Point>* points,Line line){
	if (points == nullptr) throw exception();
	double x = 0, y = 0;
	const double A2 = line.A,B2 = line.B,C2 = line.C;
	const double m = A * B2 - A2 * B;
	if (m == 0) return;
	x = (C2*B - C * B2)*1.0 / m;
	y = (C*A2 - C2 * A)*1.0 / m;
	points->insert({x,y});
	//cout << new_point.x << " " << new_point.y << endl;//
}

void Line::getIntersectPoint(set<Point>* points, Circle circle) {
	if (points == nullptr) throw exception();
	double x=0, y=0;
	const double cx = circle.cx, cy = circle.cy, r = circle.r;
	const double dis = (A*cx+B*cy+C) / sqrt(A*A+B*B);
		if (B != 0) { //直线y=kx+d   圆(x-cx)^2+(y-cy)^2=r^2
			const double k = -1 * A / B,d=-1*C/B;
			const double a = (1 + k * k);
			const double b = -1 * (2 * cx + 2 * cy*k-2*k*d);
			const double c=cx*cx+d*d+cy*cy-2*cy*d-r*r;
			if (equal(b*b,4*a*c)) {
				x = (-b / 2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << new_point.x << " 1 " << new_point.y << endl;//
			}
			else if (b*b - 4 * a*c > 0) {
				const double delt = sqrt(b*b - 4 * a*c);
				x = (-b+ delt)/ (2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << new_point1.x << " 2 " << new_point1.y << endl;//

				x = (-b-delt) / (2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << new_point2.x << "  3 " << new_point2.y << endl; //
			}
		}
		else {
			const double x0 = -C / A; //直线:x=-C/A  圆(x-cx)^2+(y-cy)^2=r^2
			if (equal(x0 - cx, r)) {
				x = x0;
				y = cy;
				points->insert({x,y});
				//cout << new_point.x << " 4 " << new_point.y << endl;//
			}
			else if (x0 - cx < r) {
				x = x0;
				y = cy+sqrt(r*r - (x0 - cx)*(x0 - cx));
				points->insert({x,y});
				//cout << new_point1.x << " " << new_point1.y << endl;//

				x = x0;
				y = cy-sqrt(r*r - (x0 - cx)*(x0 - cx));
				points->insert({x,y});
				//cout << new_point2.x << " " << new_point2.y << endl;//

			}
		}
}

void Circle::getIntersectPoint(set<Point>* points, Circle circle) {
	if (points == nullptr) throw exception();
	const double cx1 = circle.cx, cy1 = circle.cy, r1 = circle.r;
	const double dis = sqrt((cx - cx1)*(cx - cx1) + (cy - cy1)*(cy - cy1));
	if (dis < r - r1 || dis<r1 - r || dis>r + r1) return;
	const double a = 2 * r1*(cx1 - cx);
	const double b = 2 * r1*(cy1 - cy);
	const double c = r * r - r1 * r1 - (cx1 - cx)*(cx1 - cx) - (cy1-cy)*(cy1-cy);

	const double p = a * a + b * b;
	const double q = -2 * a*c;
	const double r = c * c - b * b;
	
	if (equal(sqrt(q*q - 4 * p*r), 0)||sqrt(q*q - 4 * p*r)>0) {
		double x=0, y=0;
		const double cos1 = (-q + sqrt(q*q - 4 * p*r)) / (2 * p);
		double sin1 = sqrt(1 - cos1 * cos1);
		x = r1 * cos1 + cx1;
		y = r1 * sin1 + cy1;
		if (equal((x - cx1)*(x - cx1) + (y - cy1)*(y - cy1), r1*r1)) ;
		else {
			sin1 = -sin1;
			y = r1 * sin1 + cy1;
		}
		points->insert({x,y});
		//cout << new_point1.x << " " << new_point1.y << endl;//

		const double cos2 = (-q - sqrt(q*q - 4 * p*r)) / (2 * p);
		double sin2 = sqrt(1 - cos2 * cos2);
		x = r1 * cos2 + cx1;
		y = r1 * sin2 + cy1;
		if (equal((x - cx1)*(x - cx1) + (y - cy1)*(y - cy1), r1*r1)) ;
		else {
			sin2 = -sin2;
			y = r1 * sin2 + cy1;
		}
		points->insert({x,y});
		//cout << new_point2.x << " " << new_point2.y << endl;//
	}
}