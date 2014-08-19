#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

typedef struct ListNode ListNode;

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
	ListNode *first = new ListNode(0), *p = first;
	int c = 0;
	
	ListNode *p1, *p2;
	for (p1 = l1, p2 = l2; p1 && p2; p1=p1->next, p2=p2->next) {
		int k = p1->val + p2->val + c;
		ListNode *l = new ListNode(k%10);
		p->next = l; p = l;
		c = k / 10;		
	}
	ListNode *r = p1? p1: p2;
	if (r || c) {
		for (; r; r = r->next) {
			int k = r->val + c;
			ListNode *l = new ListNode(k%10);
			p->next = l; p = l;
			c = k / 10;
		}
		if (c) {
			ListNode *l = new ListNode(c);
			p->next = l;
		}
	}
	return first->next;
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
