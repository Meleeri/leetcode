#include <stdio.h>

const int MIN = 0x1 << (sizeof(int)*8-1);

inline int max(int a, int b) {
	return a>b? a: b;
}

int maxSubArray(int A[], int n) {
	int maxSum = A[0], curSum = 0;
	for (int i = 0; i < n; ++ i) {
		curSum = curSum>0? A[i]: curSum+A[i];
		maxSum = max(maxSum, curSum);
	}
	return maxSum;
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}