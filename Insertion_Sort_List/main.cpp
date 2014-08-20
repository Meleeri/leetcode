#include <stdio.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void insert(ListNode **head, int val) {
	ListNode *node = new ListNode(val);
	node->next = *head;
	*head = node;
}

ListNode *insertionSortList(ListNode *head) {
	if (!head) return NULL;
	ListNode *curHead = head;
	ListNode *entry = head->next, *curTail = head;
	
	while (entry) {
		ListNode *n = entry->next;
		ListNode *q = curHead, *p = NULL;
		
		for (; q && q != entry; q = q->next) {
			if (q->val > entry->val) break;
			p = q;
		}
		
		if (q == entry) {
			curTail = entry;
		}
		
		else if (!p) {
			entry->next = curHead; curHead = entry;
		}
		else {
			entry->next = p->next; p->next = entry;
		}
		
		curTail->next = n;
		entry = n;
	}
	
	return curHead;
}

void print(ListNode *node) {
	for (;node; node = node->next) {
		printf("%d ", node->val);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	ListNode *head = NULL;
	insert(&head, 1);
	insert(&head, 3);
	insert(&head, 4);
	insert(&head, 2);
	insert(&head, 5);
	
	print(head);
	ListNode *result = insertionSortList(head);
	print(result);
	return 0;
}
