#include <iostream>
#include <vector>
#include <stack>
#include <iterator>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL){}
};

typedef struct TreeNode TreeNode;

vector<int> postorderTraversal(TreeNode *root) {
	vector<int> s;
	stack<TreeNode*> s1;
	stack<bool> s2;
	
	TreeNode *p = root;
	while (p || !s1.empty()) {
		while (p) {
			s1.push(p);
			s2.push(true);
			p = p->left;
		}
		p = s1.top();
		bool& flag = s2.top();
		if (flag) {
			p = p->right;
			flag = false;
		}
		else {
			s1.pop();
			s2.pop();
			s.push_back(p->val);
			p = NULL;
		}
	}
	return s;
}

int main(int argc, char *argv[]) {
	TreeNode l(1);
	TreeNode r(2);
	TreeNode p(3);
	p.left = &l; p.right = &r;
	auto result = postorderTraversal(&p);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	return 0;
}