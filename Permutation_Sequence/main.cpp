#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void permutate(bool& flag, int m, int n, int& k, bool visited[], string& s, string& result) {
	if (flag) return;
	if (k == 0) {result = s; flag = true; return;}
	if (m == n) --k;

	for (int i = 1; i <= n; ++ i) {
		if (!visited[i]) {
			visited[i] = true;
			s.push_back('0'+i);
			permutate(flag, m+1, n, k, visited, s, result);
			s.pop_back();
			visited[i] = false;
		}
	}
}

string getPermutation2(int n, int k) {
	bool visited[16];
	string s, result;
	bool flag = false;
	permutate(flag, 1, n, k, visited, s, result);
	return result;
}

string getPermutation(int n, int k) {
    if (n <= 0 || k <= 0) return "";
    vector<int> factor(n + 1, 1);
    vector<int> array(n, 1);
    string s(n, '0');

    for (int i = 1; i < n; i++) {
        factor[i] = factor[i - 1] * i;
        array[i] = i + 1;
    }

    int j = n;
    for (int i = 0; i < n; i++) {
        int count = k ? (k-1)/factor[j-1] : j - 1;
        k = k%factor[j-1];
        if (count > n) break;
        s[i] += array[count];
        array.erase(array.begin() + count);
        j--;
    }

    return s;
}

int main(int argc, char **argv)
{
	string s = getPermutation(8, 8590);
	cout << s << endl;
	return 0;
}
