#include<iostream>
#include<set>
#include<vector>
#include<fstream>
#include"obj.h"

using namespace std;

int main(int argv,char** args)
{
	if (args == nullptr) throw exception();
	ifstream input;
	ofstream output;
	set<Point> points;
	vector<Line> lines;
	vector<Circle> circles;
	int n=0,lines_size=0,circles_size=0;
	char ch='\0';
	double x1=0, y1=0, x2=0, y2=0;
	double x0=0, y0=0, r=0;
	
	if (argv == 5&&strcmp(args[1], "-i") == 0 && strcmp(args[3], "-o") == 0) {
		input=ifstream(args[2]);
		output=ofstream(args[4]);
		input >> n;
		
		for (int i = 0; i < n; i++) {
			input >> ch;
			if (ch == 'L') {
				input >> x1 >> y1 >> x2 >> y2;
				lines.push_back({x1,y1,x2,y2});
			}
			else if(ch=='C'){
				input >> x0 >> y0 >> r;
				circles.push_back({x0,y0,r});
			}
		}

		lines_size = lines.size();
		circles_size = circles.size();
		//cout << lines_size << " " << circles_size << endl;
		for (int i = 0; i < lines_size; i++) {
			for (int j = i + 1; j < lines_size; j++) {
				lines.at(i).getIntersectPoint(&points,lines.at(j));
			}
		}

		for (int i = 0; i < lines_size; i++) {
			for (int j = 0; j < circles_size; j++) {
				lines.at(i).getIntersectPoint(&points, circles.at(j));
			}
		}

		for (int i = 0; i < circles_size; i++) {
			for (int j = i+1; j < circles_size; j++) {
				circles.at(i).getIntersectPoint(&points, circles.at(j));
			}
		}
		output << points.size();
	}
}