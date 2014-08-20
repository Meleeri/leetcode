#include <stdio.h>

int binsearch(int a[], int len, int elem) {
	int i = 0, mid = len>>1;
	while (mid < len) {
		if (a[mid] < elem) i = mid+1;
		else len = mid;
		mid = (i+len)>>1;
	}
	return mid;
}

int max(int a, int b) {
	return a>b? a: b;
}

double median(int a[], int a_len, int b[], int b_len) {
	int k;
	int low = 0, high = a_len;
	int a_idx = (low+high)>>1, b_idx = binsearch(b, b_len, a[a_idx]);
	k = a_idx+b_idx;
	
	while (a_idx < high) {
		if (k == (a_len+b_len)>>1) {
			return (a_len+b_len)&1? a[a_idx]: (a_idx? (a[a_idx]+a[a_idx-1])/2.0: (a[a_idx]+b[b_len-1])/2.0);
		}
		if (k < ((a_len+b_len)>>1)) low = a_idx+1;
		else high = a_idx;
		a_idx = (low+high)>>1;
		b_idx = binsearch(b, b_len, a[a_idx]);
		k = a_idx+b_idx;
	}

	low = 0, high = b_len;
	b_idx = (low+high)>>1, a_idx = binsearch(a, a_len, b[b_idx]);
	k = a_idx+b_idx;
	
	while (b_idx < high) {
		if (k == (a_len+b_len)>>1) {
			return (a_len+b_len)&1? b[b_idx]: (b_idx? (b[b_idx]+b[b_idx-1])/2.0: (b[b_idx]+a[a_len-1])/2.0);
		}
		if (k < ((a_len+b_len)>>1)) low = b_idx+1;
		else high = b_idx;
		b_idx = (low+high)>>1;
		a_idx = binsearch(a, a_len, b[b_idx]);
		k = a_idx+b_idx;
	}
}

int main(int argc, char **argv)
{
	int a[] = {1};
	int b[] = {1};
	
	double idx = median(a, 1, b, 1);
	
	printf("%lf\n", idx);
	return 0;
}
