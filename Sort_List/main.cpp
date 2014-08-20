#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

ListNode* merge(ListNode *l1, ListNode *l2) {
	ListNode tmp(0), *p = &tmp;
	while (l1 && l2) {
		if (l1->val <= l2->val) p->next = l1, p = l1, l1 = l1->next;
		else  p->next = l2, p = l2, l2 = l2->next;
	}
	while (l1) p->next = l1, p = l1, l1=l1->next;
	while (l2) p->next = l2, p = l2, l2=l2->next;
	return tmp.next;
}

ListNode* sortList(ListNode *head) {
	ListNode *p1 = head, *p2 = head, *partition = head;
	while (p2) {
		partition = p1, p1 = p1->next;
		p2 = p2->next; if (p2) p2 = p2->next;
	}
	if (p1) {
		partition->next = NULL;
		head = sortList(head); p1 = sortList(p1);
		return merge(head, p1);
	}
	else 
		return head;
}

ListNode *merge2(ListNode *p1, int step1, ListNode *p2, int step2) {
	
}

ListNode *sortList2(ListNode *head) {
	
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	ListNode *a[16];
	for (int i = 0; i < 16; ++ i) a[i] = new ListNode(rand());
	for (int i = 0; i < 15; ++ i) a[i]->next = a[i+1];
	
	ListNode *p = sortList(a[0]);
	for (; p; p = p->next) printf("%d ", p->val);
	for (int i = 0; i < 16; ++ i) delete a[i];
	return 0;
}
