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
	cr = r;
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
	//cout << x << " 13 " << y << endl;//
}

void Line::getIntersectPoint(set<Point>* points, Circle circle) {
	if (points == nullptr) throw exception();
	double x=0, y=0;
	const double cx = circle.cx, cy = circle.cy, cr = circle.cr;
	const double dis = (A*cx+B*cy+C) / sqrt(A*A+B*B);
		if (B != 0) { //Ö±Ïßy=kx+d   Ô²(x-cx)^2+(y-cy)^2=r^2
			const double k = -1 * A / B,d=-1*C/B;
			const double a = (1 + k * k);
			const double b = -1 * (2 * cx + 2 * cy*k-2*k*d);
			const double c=cx*cx+d*d+cy*cy-2*cy*d-cr*cr;
			if (equal(b*b,4*a*c)) {
				x = (-b / 2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << x << " 1 " << y << endl;//
			}
			else if (b*b - 4 * a*c > 0) {
				const double delt = sqrt(b*b - 4 * a*c);
				x = (-b+ delt)/ (2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << x << " 2 " << y << endl;//

				x = (-b-delt) / (2 * a);
				y = k * x + d;
				points->insert({x,y});
				//cout << x << "  3 " << y << endl; //
			}
		}
		else {
			const double x0 = -C / A; //直线:x=-C/A  圆：(x-cx)^2+(y-cy)^2=r^2
			if (equal(fabs(x0 - cx), cr)) {
				x = x0;
				y = cy;
				points->insert({x,y});
				//cout << x << " 4 " << y << endl;//
			}
			else if (fabs(x0 - cx) < cr) {
				x = x0;
				y = cy+sqrt(cr*cr - (x0 - cx)*(x0 - cx));
				points->insert({x,y});
				//cout << x << " 5 " << y << endl;//

				x = x0;
				y = cy-sqrt(cr*cr - (x0 - cx)*(x0 - cx));
				points->insert({x,y});
				//cout << x << " 6 " << y << endl;//
			}
		}
}

void Circle::getIntersectPoint(set<Point>* points, Circle circle) {
	if (points == nullptr) throw exception();
	const double cx1 = circle.cx, cy1 = circle.cy, cr1 = circle.cr;
	const double dis = sqrt((cx - cx1)*(cx - cx1) + (cy - cy1)*(cy - cy1));
	if (dis < cr - cr1 || dis<cr1 - cr || dis>cr + cr1) return;
	const double a = 2 * cr1*(cx1 - cx);
	const double b = 2 * cr1*(cy1 - cy);
	const double c = cr * cr - cr1 *cr1 - (cx1 - cx)*(cx1 - cx) - (cy1-cy)*(cy1-cy);

	const double p = a * a + b * b;
	const double q = -2 * a*c;
	const double r = c * c - b * b;
	
	if (equal(q*q - 4 * p*r, 0)||q*q - 4 * p*r>0) {
		double x=0, y=0;
		const double cos1 = (-q + sqrt(q*q - 4 * p*r)) / (2 * p);
		double sin1 = sqrt(1 - cos1 * cos1);
		x = cr1 * cos1 + cx1;
		y = cr1 * sin1 + cy1;
		if (equal((x - cx)*(x - cx) + (y - cy)*(y - cy), cr*cr)) {
			points->insert({ x,y });
			//cout << x << " 9 " << y << endl;//
		}
		y = -sin1*cr1 + cy1;
		if (equal((x - cx)*(x - cx) + (y - cy)*(y - cy), cr*cr)) {
			points->insert({ x,y });
			//cout << x << " 7 " << y << endl;//
		}

		const double cos2 = (-q - sqrt(q*q - 4 * p*r)) / (2 * p);
		double sin2 = sqrt(1 - cos2 * cos2);
		x = cr1 * cos2 + cx1;
		y = cr1 * sin2 + cy1;
		if (equal((x - cx)*(x - cx) + (y - cy)*(y - cy), cr*cr)) {
			points->insert({ x,y });
			//cout << x << " 10 " << y << endl;//
		}
		y = -sin2*cr1 + cy1;
		if (equal((x - cx)*(x - cx) + (y - cy)*(y - cy), cr*cr)){
			points->insert({ x,y });
			//cout << x << " 11 " << y << endl;//
		}
	}
}