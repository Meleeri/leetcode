#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_set>

#define MAX 1024

using namespace std;

bool visited[MAX][MAX];
bool dp[MAX][MAX];

bool dfs(string& s, int start, int end, unordered_set<string>& dict) {
	if (visited[start][end]) return dp[start][end];
	if (start == end) goto TRUE;
	
	for (int i = start+1; i <= end; ++ i) {
		bool ans = false;
		if (dict.find(s.substr(start, i-start)) != dict.end()) {
			ans = ans || dfs(s, i, end, dict);
		}
		if (ans) goto TRUE;
	}
	visited[start][end] = true;
	return false;
TRUE:
	dp[start][end] = visited[start][end] = true; return true;
}
bool wordBreak(string s, unordered_set<string>& dict) {
	memset(dp, 0, sizeof(bool)*MAX*MAX);
	memset(visited, 0, sizeof(bool)*MAX*MAX);
	return dfs(s, 0, s.size(), dict);
}

int main(int argc, char **argv)
{
	unordered_set<string> dict, dict2;
	dict.insert("a"); 
	dict.insert("aa");
	dict.insert("aaa");
	dict.insert("aaaa");
	dict.insert("aaaaa");
	dict.insert("aaaaaa");
	dict.insert("aaaaaaa");
	dict.insert("aaaaaaaa");
	cout << wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", dict) << endl;
	
	dict2.insert("a");
	cout << wordBreak("a", dict);
	return 0;
}
