#include <iostream>

class Node
{
public:

	int val;
	Node* next;
	Node* prev;

	Node(int val)
	{
		this->val = val;
		next = nullptr;
		prev = nullptr;
	}
};

class DList
{
private:
	Node* head = nullptr;
public:
	//пересечениe 2-х множеств
	static DList inter(const DList& a, const DList& b)
	{
		DList inter;
		if (a.head != nullptr && &b != &a)
		{
			Node* tmp = nullptr;
			tmp = a.head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				if (b.find_ptr(tmp->val)) // элемент есть в обоих множествах
				{
					inter.push(tmp->val);
				}
				tmp = tmp->next;
			}
		}
		else if (&b == &a) return a;
		return inter;
	}

	DList operator+(const DList& b) const
	{
		DList out(*this);

		if (b.head != nullptr && &b != this)
		{
			Node* tmp = nullptr;
			tmp = b.head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				out.push(tmp->val);
				tmp = tmp->next;
			}
		}

		return out;
	}

	void operator+=(const DList& b)
	{
		if (b.head != nullptr && &b != this)
		{
			Node* tmp = nullptr;
			tmp = b.head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				this->push(tmp->val);
				tmp = tmp->next;
			}
		}
	}

	void operator=(const DList& b)
	{
		if (&b != this)
		{
			this->clear();

			if (b.head != nullptr)
			{
				Node* tmp = nullptr;
				tmp = b.head;

				while (tmp->prev != nullptr)
				{
					tmp = tmp->prev;
				}

				while (tmp != nullptr)
				{
					this->push(tmp->val);
					tmp = tmp->next;
				}
			}
		}
	}

	void operator=(DList&& move) noexcept
	{
		if (&move != this)
		{
			this->clear();

			this->head = move.head;
			move.head = nullptr;
		}
	}

	DList operator-(const DList& b) const
	{
		DList inter;
		if (head != nullptr && b.head != nullptr && &b != this)
		{
			Node* tmp = nullptr;
			tmp = b.head;
			inter = *this;

			while (tmp->prev != nullptr) tmp = tmp->prev;

			while (tmp != nullptr)
			{
				inter.pop(tmp->val);
				tmp = tmp->next;
			}
		}
		else if (b.head == nullptr && &b != this) return *this;
		return inter;
	}

	void operator-=(const DList& b)
	{
		if (head != nullptr && b.head != nullptr && &b != this)
		{
			Node* tmp = nullptr;
			tmp = b.head;

			while (tmp->prev != nullptr) tmp = tmp->prev;

			while (tmp != nullptr)
			{
				this->pop(tmp->val);
				tmp = tmp->next;
			}
		}
		else if (&b == this) clear();
	}

	//cardinality - мощность множества
	int cardin() const
	{
		int out = 0;
		if (head != nullptr)
		{
			Node* tmp = nullptr;
			tmp = head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				out++;
				tmp = tmp->next;
			}
		}
		return out;
	}

	//добавление нового элемента в множество
	void push(int data)
	{
		Node* node = new Node(data);

		if (head == nullptr)
		{
			head = node;
		}
		else
		{
			Node* tmp;
			tmp = head;

			if (data > tmp->val)
			{
				while (!(tmp->next == nullptr || tmp->next->val > data))
				{
					tmp = tmp->next;
				}

				if (tmp->val != data)
				{
					node->next = tmp->next;
					node->prev = tmp;

					if (tmp->next != nullptr)
					{
						tmp->next->prev = node;
					}

					tmp->next = node;
				}
				else delete node;
			}
			else if (data < tmp->val)
			{
				while (!(tmp->prev == nullptr || tmp->prev->val < data))
				{
					tmp = tmp->prev;
				}

				if (tmp->val != data)
				{
					node->next = tmp;
					node->prev = tmp->prev;

					if (tmp->prev != nullptr)
					{
						tmp->prev->next = node;
					}

					tmp->prev = node;
				}
				else delete node;
			}
		}
	}

	//удаление элемента
	void pop(int val)
	{
		Node* del = find_ptr(val);
		if (del != nullptr)
		{
			if (del->next == nullptr && del->prev == nullptr)
			{
				head = nullptr;

				delete del;
			}
			else if (del->next == nullptr)
			{
				del->prev->next = nullptr;

				if (del == head)
				{
					head = del->prev;
				}

				delete del;
			}
			else if (del->prev == nullptr)
			{
				del->next->prev = nullptr;

				if (del == head)
				{
					head = del->next;
				}

				delete del;
			}
			else
			{
				if (del == head)
				{
					head->next->prev = head->prev;
					head->prev->next = head->next;
					head = head->next;

					delete del;
				}
				else
				{
					del->next->prev = del->prev;
					del->prev->next = del->next;

					delete del;
				}
			}
		}
	}

	//вывод множества
	void print() const
	{
		if (head != nullptr)
		{
			Node* tmp = nullptr;
			tmp = head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				printf("%2i\n", tmp->val);
				tmp = tmp->next;
			}
		}
	}

	void clear()
	{
		if (head != nullptr)
		{
			Node* tmp;
			Node* wipe;
			tmp = head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp->next != nullptr)
			{
				wipe = tmp;
				tmp = tmp->next;
				delete wipe;
			}

			delete tmp;
		}

		head = nullptr;
	}

	bool find(int val) const
	{
		Node* tmp = nullptr;
		tmp = head;

		if (head != nullptr)
		{
			if (head->val <= val)
			{
				while (tmp->next != nullptr)
				{
					if (tmp->val == val)
					{
						break;
					}

					tmp = tmp->next;
				}
				if (tmp->val != val)
				{
					return false;
				}
				else return true;
			}
			else
			{
				while (tmp->prev != nullptr)
				{
					if (tmp->val == val)
					{
						break;
					}

					tmp = tmp->prev;
				}
				if (tmp->val != val)
				{
					return false;
				}
				else return true;
			}
		}
		else return false;
	}

	DList()
	{
	}

	//конструктор копирования
	DList(const DList& copy)
	{
		if (copy.head != nullptr)
		{
			Node* tmp = nullptr;
			tmp = copy.head;

			while (tmp->prev != nullptr)
			{
				tmp = tmp->prev;
			}

			while (tmp != nullptr)
			{
				this->push(tmp->val);
				tmp = tmp->next;
			}
		}
	}

	//конструктор перемещения
	DList(DList&& move) noexcept
	{
		if (move.head != nullptr)
		{
			this->head = move.head;

			move.head = nullptr;
		}
	}

	~DList()
	{
		clear();
	}
private:
	Node* find_ptr(int val) const
	{
		Node* tmp = nullptr;
		tmp = head;

		if (head != nullptr)
		{
			if (head->val <= val)
			{
				while (tmp->next != nullptr)
				{
					if (tmp->val == val)
					{
						break;
					}

					tmp = tmp->next;
				}
				if (tmp->val != val)
				{
					return nullptr;
				}
				else return tmp;
			}
			else
			{
				while (tmp->prev != nullptr)
				{
					if (tmp->val == val)
					{
						break;
					}

					tmp = tmp->prev;
				}
				if (tmp->val != val)
				{
					return nullptr;
				}
				else return tmp;
			}
		}
		else return nullptr;
	}
};

int main()
{
	DList a;
	DList b;

	for (int i = 1; i < 6; i++) b.push(i);

	b.pop(5);
}


