#include <iostream>
using namespace std;

class Node
{
public:

	int Key;
	Node* Left;
	Node* Right;
	int Height;
	int Counter;

	Node(int key)
	{
		this->Key = key;
		this->Left = nullptr;
		this->Right = nullptr;
		this->Height = 1;
		this->Counter = 1;
	}
};

class AVL
{
private:

	int Sum = 0;
	int Amount = 0;

	int Height(Node* N)
	{
		if (N == NULL)
			return 0;
		return N->Height;
	}

	int Max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	Node* RightRotate(Node* y)
	{
		Node* x = y->Left;
		Node* T2 = x->Right;
		x->Right = y;
		y->Left = T2;
		y->Height = Max(Height(y->Left),
			Height(y->Right)) +
			1;
		x->Height = Max(Height(x->Left),
			Height(x->Right)) +
			1;
		return x;
	}

	Node* LeftRotate(Node* x)
	{
		Node* y = x->Right;
		Node* T2 = y->Left;
		y->Left = x;
		x->Right = T2;
		x->Height = Max(Height(x->Left),
			Height(x->Right)) +
			1;
		y->Height = Max(Height(y->Left),
			Height(y->Right)) +
			1;
		return y;
	}

	int GetBalanceFactor(Node* N)
	{
		if (N == nullptr)
			return 0;
		return Height(N->Left) - Height(N->Right);
	}

	Node* InsertNode(Node* node, int key)
	{
		if (node == nullptr)
		{
			Amount++;
			Sum += key;
			return new Node(key);
		}

		if (key < node->Key)
			node->Left = InsertNode(node->Left, key);
		else if (key > node->Key)
			node->Right = InsertNode(node->Right, key);
		else
		{
			node->Counter++;
			Amount++;
			Sum += node->Key;
			return node;
		}

		node->Height = 1 + Max(Height(node->Left),
			Height(node->Right));
		int balanceFactor = GetBalanceFactor(node);
		if (balanceFactor > 1)
		{
			if (key < node->Left->Key)
			{
				return RightRotate(node);
			}
			else if (key > node->Left->Key)
			{
				node->Left = LeftRotate(node->Left);
				return RightRotate(node);
			}
		}

		if (balanceFactor < -1)
		{
			if (key > node->Right->Key)
			{
				return LeftRotate(node);
			}
			else if (key < node->Right->Key)
			{
				node->Right = RightRotate(node->Right);
				return LeftRotate(node);
			}
		}

		return node;
	}

	Node* NodeWithMimumValue(Node* node)
	{
		Node* current = node;
		while (current->Left != nullptr)
			current = current->Left;

		return current;
	}

	Node* Pop(Node* node, int key)
	{
		if (node == nullptr) return node;
		if (key < node->Key)
			node->Left = Pop(node->Left, key);
		else
			if (key > node->Key)
				node->Right = Pop(node->Right, key);
			else
			{
				if ((node->Left == nullptr) || (node->Right == nullptr))
				{
					Node* temp = node->Left ? node->Left : node->Right;
					if (temp == nullptr)
					{
						temp = node;
						node = nullptr;
					}
					else *node = *temp;

					Sum -= temp->Key * temp->Counter;
					Amount -= temp->Counter;
					delete temp;
				}
				else
				{
					Node* temp = NodeWithMimumValue(node->Right);
					node->Key = temp->Key;
					node->Right = Pop(node->Right, temp->Key);
				}
			}

		if (node == nullptr)
			return node;

		node->Height = 1 + Max(Height(node->Left),
			Height(node->Right));
		int balanceFactor = GetBalanceFactor(node);
		if (balanceFactor > 1)
		{
			if (GetBalanceFactor(node->Left) >= 0)
			{
				return RightRotate(node);
			}
			else
			{
				node->Left = LeftRotate(node->Left);
				return RightRotate(node);
			}
		}

		if (balanceFactor < -1)
		{
			if (GetBalanceFactor(node->Right) <= 0)
			{
				return LeftRotate(node);
			}
			else
			{
				node->Right = RightRotate(node->Right);
				return LeftRotate(node);
			}
		}

		return node;
	}

	void PrintTree(Node* node, string indent, bool last)
	{
		if (node != nullptr)
		{
			cout << indent;
			if (node == Root)
			{
				cout << "Head--->";
				indent += "   ";
			}
			else if (last)
			{
				cout << "R--->";
				indent += "   ";
			}
			else
			{
				cout << "L--->";
				indent += "|  ";
			}

			if (node->Counter == 1) cout << node->Key << endl;
			else cout << node->Key << " x " << node->Counter << endl;

			PrintTree(node->Left, indent, false);
			PrintTree(node->Right, indent, true);
		}
	}

	void PrintInOrder(Node* root)
	{
		if (root != nullptr)
		{
			if (root->Left != nullptr)
			{
				PrintInOrder(root->Left);
			}

			for (int i = 0; i < root->Counter; i++) cout << root->Key << " ";

			if (root->Right != nullptr)
			{
				PrintInOrder(root->Right);
			}
		}
	}

	void Clear(Node* node)
	{
		if (node != nullptr)
		{
			Node* R = node->Right;
			Node* L = node->Left;

			Sum -= node->Key * Root->Counter;
			Amount -= node->Counter;

			delete node;

			Clear(R);
			Clear(L);
		}
	}

	Node* Root = nullptr;

public:

	void Insert(int Key)
	{
		Root = InsertNode(Root, Key);
	}

	void Pop(int Key)
	{
		Root = Pop(Root, Key);
	}

	void Print()
	{
		if (Root != nullptr)
		{
			PrintTree(Root, "", true);
		}
	}

	void PrintInOrder()
	{
		PrintInOrder(Root);
		cout << endl;
	}

	int GetAvgKey()
	{
		if (Amount == 0) return 0;
		return Sum / Amount;
	}

	~AVL()
	{
		Clear(Root);
	}
};

/*
Функции:
 * Печать дерева - print()
 * Печать дерева в порядке возрастания - printInOrder()
 * Добавление элемента - insert(int key)
 * Удаление элемента - deleteNode(int key)
 * Среднее значение ключа по дереву - getAvgKey()
*/

int main()
{
	AVL tree;

	cout << endl;
}

