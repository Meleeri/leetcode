#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct adjvex {
	struct edge *first;
	int in_deg;
	
	adjvex(): first(NULL), in_deg(0) {}
};

struct edge {
	struct adjvex *v;
	struct edge *next;
	
};

typedef struct adjvex adjvex;
typedef struct edge edge;

void add_edge(adjvex *u, adjvex *v) {
	edge *e = new edge;
	e->v = v;
	e->next = u->first;
	u->first = e;
	
	++ v->in_deg;
}

int candy(vector<int> &ratings) {
	vector<adjvex*> vertices(ratings.size());
	for (int i = 0; i < ratings.size(); ++ i) {
		vertices[i] = new adjvex;
	}
	
	for (int i = 1; i < ratings.size(); ++ i) {
		if (ratings[i] < ratings[i-1]) add_edge(vertices[i], vertices[i-1]);
		if (ratings[i] > ratings[i-1]) add_edge(vertices[i-1], vertices[i]);
	}
	
	
	stack<adjvex*> s;
	for (int i = 0; i < ratings.size(); ++ i) {
		if (vertices[i]->in_deg == 0) s.push(vertices[i]);
	}
	
	int per = 1, all = 0;
	while (!s.empty()) {
		adjvex *v = s.top(); s.pop();
		for (edge *e = v->first; e; e = e->next) {
			all += per;
			if (--(e->v->in_deg) == 0) {
				s.push(e->v);
			}
		}
		++ per;
	}
	return all;
}
int main(int argc, char **argv)
{
	
	return 0;
}
