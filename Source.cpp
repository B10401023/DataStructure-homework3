#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int data;
	Node *left;
	Node *right;
	Node() { left = 0; right = 0; }
};

class BST
{
private:
	Node *root;
	Node *currentNode;
	Node *pastNode;
public:
	BST();
	void insertion(int);
	void deletion();
	void levelorder();
	int computsize(Node *);
	Node *search(int);
	int computsize(int);
};

BST::BST()
{
	root = NULL;
}

void BST::insertion(int p)
{
	if (root)
	{
		currentNode = root;
		while (currentNode)
		{
			if (currentNode->data > p)
			{
				pastNode = currentNode;
				currentNode = currentNode->left;
			}
			else if (currentNode->data < p)
			{
				pastNode = currentNode;
				currentNode = currentNode->right;
			}
		}
		Node *leaf = new Node;
		leaf->data = p;
		if (pastNode->data > p)
			pastNode->left = leaf;
		else if (pastNode->data < p)
			pastNode->right = leaf;
	}
	else
	{
		root = new Node;
		root->data = p;
	}
}

void BST::deletion()
{
	currentNode = root;
	while (currentNode->right)
	{
		pastNode = currentNode;
		currentNode = currentNode->right;
	}
	if (currentNode == root)
	{
		if (currentNode->left)
			root = currentNode->left;
		else
			root = NULL;
	}
	else
	{
		if (currentNode->left)
			pastNode->right = currentNode->left;
		else
			pastNode->right = NULL;
	}
	delete currentNode;
}

Node *BST::search(int p)
{
	currentNode = root;
	while (currentNode)
	{
		if (p > currentNode->data)
			currentNode = currentNode->right;
		else if (p < currentNode->data)
			currentNode = currentNode->left;
		else
		{
			currentNode = currentNode->left;
			return currentNode;
		}
	}
}

void BST::levelorder()
{
	std::queue<Node *> Myqueue;
	currentNode = root;
	Myqueue.push(root);
	while (currentNode)
	{
		currentNode = Myqueue.front();
		cout << currentNode->data << " ";
		if (currentNode->left)
			Myqueue.push(currentNode->left);
		if (currentNode->right)
			Myqueue.push(currentNode->right);
		Myqueue.pop();
		if (Myqueue.empty())
			return;
	}
}

int BST::computsize(int p)
{
	return (computsize(search(p)));
}

int BST::computsize(Node *cur)
{
	int count = 1;
	if (cur->left)
	{
		count = count + computsize(cur->left);
	}
	if (cur->right)
	{
		count = count + computsize(cur->right);
	}
	return count;
}

void main()
{
	BST tree;
	while (1)
	{
		int NUM, j ,times = 0, p;
		cout << "Amount:";
		cin >> NUM;
		cout << "Please enter a sequence of integers." << endl;
		for (int times = 0; times < NUM; times++)
		{
			cin >> p;
			tree.insertion(p);
		}
		tree.levelorder();
		cout << endl;
		cout << "1.Insert\n" << "2.Delete\n" << "3.Find out the total number of elements in the left subtree\n" << "4.Restart\n" << endl;
		while (1)
		{
			cin >> j;
			if (j == 1)
			{
				cin >> p;
				tree.insertion(p);
				tree.levelorder();
				cout << "\n";
			}
			else if (j == 2)
			{
				tree.deletion();
				tree.levelorder();
				cout << "\n";
			}
			else if (j == 3)
			{
				int count = 0;
				cin >> p;
				cout << tree.computsize(p) << endl;
			}
			else if (j == 4)
				break;
		}
	}
}