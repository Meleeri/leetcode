#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
	int num;
	struct Node* left;
	struct Node* right;
	Node(int x) : num(x), left(NULL), right(NULL) {}
};

void Serialize_a(struct Node* root, FILE* pfile)
{
	if(!root)
	{
		fprintf(pfile, "# ");
	}

	else
	{
		fprintf(pfile, "%d ", root->num);
		Serialize_a(root->left, pfile);
		Serialize_a(root->right,  pfile);
	}
}

int  Serialize(struct Node* root, char* filename)
{
	FILE* pfile = fopen(filename, "w");
	if(!pfile)
	{
		return -1;
	}

	Serialize_a(root, pfile);

	fclose(pfile);

	return 0;
}

void Deserialize_a(FILE* pfile, struct Node*& root)
{
	char str[1024];

	fscanf(pfile, "%s", str);

//	printf("%s", str);
	if(strcmp(str, "#") == 0) return;

	root = new Node(0);
	root->num = atoi(str);

	Deserialize_a(pfile, root->left);  
	Deserialize_a(pfile, root->right);   
}

int Deserialize(char* filename, struct Node*& root)
{
	FILE* pfile = fopen(filename, "r");
	if(!pfile)
	{
		return -1;
	}

	Deserialize_a(pfile, root);

	fclose(pfile);

	return 0;
}


int main()
{
	Node *node1 = new Node(30);
	Node *node2 = new Node(10);
	Node *node3 = new Node(50);
	Node *node4 = new Node(20);
	Node *node5 = new Node(45);
	Node *node6 = new Node(35);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	char filename[] = "serialize.txt";
	int status = Serialize(node1, filename);
	char filename2[] = "serializeReov.txt";
	Node *root =  NULL;
	int status1  = Deserialize(filename,  root);
	int status2 = Serialize(root, filename2);
	
	system("pause");
}
