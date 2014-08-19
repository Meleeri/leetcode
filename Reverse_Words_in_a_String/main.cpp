#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void reverseWords(string &s) {
	vector<tuple<string::iterator, string::iterator> > indices;
	string str = s;
	
	string::iterator idx_start, idx_end;
	auto x = str.begin();
	while (true) {
		while (x != str.end() && *x == ' ') ++ x;
		if (x == str.end()) break;
		string::iterator idx = x;
		while (x != str.end() && *x != ' ') ++ x;
		indices.push_back(make_tuple(idx, x));
		if (x == str.end()) break;
	}
	
	s.clear();
	for (auto i = indices.rbegin(); i != indices.rend(); ++ i) {
		tie(idx_start, idx_end) = *i;
		copy(idx_start, idx_end, back_inserter(s));
		s.push_back(' ');
	}
	if (!s.empty()) s.pop_back();
}

int main(int argc, char **argv)
{
	string s = "fuck the gfw !";
	reverseWords(s);
	cout << s << endl;
	return 0;
}
