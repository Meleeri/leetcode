#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int evalRPN(vector<string> &tokens) {
	stack<int> operand;
	for (auto i = tokens.begin(); i != tokens.end(); ++ i) {
		char c = (*i).front();
		if (isdigit(c) || (*i).size() > 1) {
			operand.push(stoi(*i));
		}
		else {
			int x = operand.top(); operand.pop();
			int y = operand.top(); operand.pop();

			switch(c) {
				case '+':
				operand.push(y+x);
				break;
				case '-':
				operand.push(y-x);
				break;
				case '*':
				operand.push(y*x);
				break;
				case '/':
				operand.push(y/x);
				break;
			}
		}
	}
	return operand.top();
}

int main(int argc, char **argv)
{
	vector<string> exp = {"0", "3", "/"};
	cout << evalRPN(exp) << endl;
	return 0;
}
