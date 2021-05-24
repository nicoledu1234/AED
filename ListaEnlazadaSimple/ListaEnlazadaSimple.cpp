#include <iostream>

using namespace std;


template<class T>
class asc {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};


template<class T>
class desc {
public:
	bool operator()(T a, T b) {
		return a > b;
	}
};
template<class T>
class Node {
public:
	T value;
	Node* next;
	Node(T v) {
		value = v;
		next = NULL;
	}
};

template<class T, class R>
class LinkedList {
	private:
		Node<T>* head;
		R r;
	public:
		LinkedList() {
			head = nullptr;
		}
		bool Find(T x, Node<T>**& p) {
			for (p = &head; *p && r((*p)->value,x) ; p = &((*p)->next));
			return *p && (*p)->value == x;
		}
		bool Insert(T x) {
			Node<T>** p;
			if (Find(x, p)) {
				return 0;
			}
			Node<T>* n = new Node<T>(x);
			n->next = *p; 
			*p=n; 
			return 1;
		}
		bool Remove(T x) {
			Node<T>** p;
			if (!Find(x, p)) {
				return 0; 
			}
			Node<T>* t = *p;
			*p =(*p)->next; 
			delete(t);
			return 1;
		}
		~LinkedList() {
			Node<T>** p;
			for (p = &head; *p ; ) {
				Node<T>* t = *p;
				*p = (*p)->next;
				delete(t);
			}
		}
		void Print() {
			if (!head) {
				cout << "Empty Linked List" << endl;
			}
			else {
				for (Node<T>* i = head; i; i = i->next) {
					cout << i->value << "->";
				}
				cout << "|| " << endl;
			}
			
		}

};



int main() {
	LinkedList<int,asc<int>> l;

	l.Insert(5);
	l.Insert(7);
	l.Insert(9);
	l.Insert(1);
	l.Insert(15);
	l.Insert(3);
	l.Insert(8);
	l.Insert(0);
	l.Insert(25);
	l.Print();
	cout << endl;
	l.Remove(5);
	l.Print();
	l.Remove(25);
	l.Print();
	l.Remove(0);
	l.Print();
	l.~LinkedList();
	l.Print();

	cout << "Lista Enlazada Simple" << endl;
	
}