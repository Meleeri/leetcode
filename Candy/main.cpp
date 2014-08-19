#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct adjvex {
	struct edge *first;
	int rating;
	
	int out_deg;
	struct adjvex(): first(NULL), rating(0), out_deg(0) {}
	struct adjvex(int r, int o): first(NULL), rating(r), out_deg(o) {}
};

struct edge {
	int index;
	struct edge *next;
};

typedef struct adjvex adjvex;
typedef struct edge edge;

void add_edge(adjvex *u, int v) {
	edge *e = new edge;
	edge->index = v;
	edge->next = u->first;
	u->first = edge;
	++ u->in_deg;
}

int candy(vector<int> &ratings) {
	vector<adjvex*> vertices(ratings.size());
	for (int i = 0; i < ratings.size(); ++ i) {
		vertices[i] = new adjvex(ratings[i], 0);
	}
	
	for (int i = 1; i < ratings.size(); ++ i) {
		if (ratings[i] < ratings[i-1]) add_edge(vertices[i-1], i);
		if (ratings[i] > ratings[i-1]) add_edge(vertices[i], i-1);
	}
	
	
	stack<adjvex*> s;
	for (int i = 0; i < ratings.size(); ++ i) {
		if (vertices[i].out_deg == 0) s.push(vertices[i]);
	}
	
	while (!s.empty()) {
		
	}
}
int main(int argc, char **argv)
{
	
	return 0;
}
