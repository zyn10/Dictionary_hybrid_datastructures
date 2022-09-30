#include<iostream>
#include<iomanip>
#include<string>
#include<string.h>
#include<fstream>
#include<algorithm>
#include <ctime>
#include<queue>
#include<cstdlib>


using namespace std;

struct Node
{
	 Node* left;
	 Node* right;
	 string data;
};
class AVL
{
	Node *root;
public:
	int height(Node *temp)
	{
		int h = 0;
		if (temp != NULL)
		{
			int L_Height = height (temp->left);
			int R_Height = height (temp->right);
			int max_height = max (L_Height, R_Height);
			h = max_height + 1;
		}
		return h;
	}
	int diff (Node * temp)
	{

		int L_Height = height(temp->left);
		int R_Height = height(temp->right);
		int B_Factor = L_Height - R_Height;
		return B_Factor;
	}
	Node *RR(Node * Parent)
	{
		Node *temp;
		temp = Parent->right;
		Parent->right = temp->left;
		temp->left = Parent;
		return temp;

	}
	Node *LL(Node * Parent)
	{
		Node *temp;
		temp = Parent->left;
		Parent->left = temp->right;
		temp->right = Parent;
		return temp;
	}
	Node *LR(Node * Parent)
	{
		Node *temp;
		temp = Parent->left;
		Parent->left = RR(temp);
		return LL(Parent);

	}
	Node *RL(Node * Parent)
	{
		Node *temp;
		temp= Parent->right;
		Parent->right = LL(temp);
		return RR(Parent);

	}
	Node *Balance(Node * temp)
	{
		int BalanceFactor = diff(temp);
		if (BalanceFactor > 1)
		{ if (diff(temp ->left) >0)
			temp = LL(temp);
		else
			temp = LR(temp);
		}
		else if (BalanceFactor < -1)
		{
			if (diff(temp->right) > 0)
				temp = RL(temp);
			else
				temp = RR(temp);
		}
		return temp;

	}
	Node *Insertion(Node *Root, string input)
	{
		if (Root == NULL) 
		{
			Root = new Node;
			Root->data = input;
			Root->left = NULL;
			Root->right = NULL;
			return Root;
		}
		else if (input < Root->data)
		{
			Root->left = Insertion(Root->left, input);
			Root = Balance(Root);
		}
		else if (input > Root->data)
		{
			Root->right = Insertion(Root->right, input);
			Root = Balance(Root);
		}
		return Root;
   }
	void Display(Node* Root)
	{
		if (!Root)
		{
			cout << "Empty Nothing to display" << endl;
			return;

		}
		queue<Node*> obj;
		obj.push(Root);
		while (!obj.empty())
		{
			Node * temp = obj.front();
			obj.pop();
			cout << temp->data << "-->";
			if(temp->left)
				obj.push(temp->left);
			if(temp->right)
				obj.push(temp->right);
		}

	}
	Node *Searching(string data, Node *Root)
	{
		if (!Root)
		{
			return NULL;
		}
		else if (data == Root->data)
			return Root;
		else if (data > Root->data)
			return Searching(data,Root->right);
		else if (data < Root->data)
			return Searching(data,Root->left);
	}
	Node *FindLargest(Node * Root)
	{
		if (!Root)
		{
			return NULL;
		}
		if (Root->right)
		{
			return FindLargest(Root->right);
		}
		else
			return Root;

	}
	Node *FindSmallest(Node * Root)
	{
		if (!Root)
		{
			return NULL;
		}
		if (Root->right)
		{
			return FindLargest(Root->left);
		}
		else
			return Root;
	}
	Node *getRoot()
	{
		return root;
	}
	AVL()
	{
		root = NULL;
	}

};
Node *Array[26];
AVL obj[26];
void insert(string NUM)
{
	Node* new_Node = new Node;
	new_Node->data = NUM;
	char c = NUM[0];
	int index = int(c - 97);
	Array[index] = obj[index].Insertion(Array[index], NUM);
}
void display()
{
	for (int i = 0; i < 26; i++)
	{
		cout << "Char = " << char(i + 97) << " -> ";
		obj[i].Display(Array[i]);
		cout << endl;
	}
}
void search(string NUM)
{
	char c = NUM[0];
	int index = (int)(c - 97);
	Node* ptr = obj[index].Searching(NUM, Array[index]);
	if (ptr)
		cout << NUM << " Found :-D" << endl;
	else
		cout << NUM << " NOt Found :-(" << endl;
}



int main()
{
	srand(time(0));
	for (int i = 0; i < 36; i++)
	{
		Array[i] = NULL;
	}
	int i = 0;
	fstream obj;
	obj.open("text.txt", ios::in);
	string t;
	int nums[100];
	for (int j = 0; j < 100; j++)
		nums[j] = rand() % 10000;
	while (!obj.eof())
	{

		getline(obj, t);
		for (int j = 0; j < 100; j++)
		{
			if (i == nums[j])
				insert(t);
		}
		i++;
	}
	obj.close();
	bool fh = true;
	int choice;
	string word;
	    system("cls");
		cout << "Hashing by Separate Chaining" << endl << endl;
		cout << "Press 1  to Insert a Word" << endl;
		cout << "Press 2  to Display All Words" << endl;
		cout << "Press 3  to Search a Word" << endl;
		cout << "Press 4  to Exit" << endl;
		cout << "Input Choice ";
	while (fh)
	{
		
		cin >> choice;
		cin.ignore();
		switch (choice)
		{ case 1:
			cout << "Enter a word you want to insert" << endl;
			getline(cin, word);
			insert(word);
			break;
		case 2:
		display();
		break;
		case 3:
		cout << "Enter a word wou want to search " << endl;
		getline(cin, word);
		search(word);
		break;
		case 4:
		fh = false;
		break;
		default:
			cout << "Invalid Choice" << endl;
	}
 }
	return 0;
}
		