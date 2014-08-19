#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

struct Point {
	int x;
	int y;
	Point(): x(0), y(0){}
	Point(int a, int b): x(a), y(b) {}
};



typedef struct Point Point;

int gcd(int m, int n) {
	if (m == 0 && n == 0) return 0;
	int k;
	while (n != 0) {
		k = m % n;
		m = n;
		n = k;
	}
	return m;
}

bool operator<(const Point &p1, const Point &p2) {
	return !(p1.x == p2.x && p1.y == p2.y);
}

Point slope(const Point &p1, const Point &p2) {
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	
	int d = gcd(dx, dy);
	if (d == 0) return Point(0, 0);
	
	if (dx/d < 0) d = -d;
	return Point(dx/d, dy/d);
}

bool straight(const Point&p, const Point& a, const Point& b) {
	int dx1 = p.x-a.x, dy1 = p.y-a.y;
	int dx2 = a.x-b.x, dy2 = a.y-b.y;
	
	return (dx1*dy2-dy1*dx2 == 0);
}


int maxPoints(vector<Points> &points) {
	map<tuple<Point, Point>, int> m;
	
	for (auto i = points.begin(); i != points.end(); ++ i) {
		for (auto j = i+1; j != points.end(); ++ j) {
			
		}
	}
}
