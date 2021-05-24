#include <iostream>
using namespace std;
template <class R>
int mod(R t, R m) {
	int mo = -1;
	if (t < 0)
		return (t * mo >= m) ? (t - (t / m * m)) + m : t + m;
	return (t >= m) ? t - (t / m * m) : t;
}

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
		for (p = &head; *p && r((*p)->value, x); p = &((*p)->next));
		return *p && (*p)->value == x;
	}
	bool Insert(T x) {
		Node<T>** p;
		if (Find(x, p)) {
			return 0;
		}
		Node<T>* n = new Node<T>(x);
		n->next = *p;
		*p = n;
		return 1;
	}
	bool Remove(T x) {
		Node<T>** p;
		if (!Find(x, p)) {
			return 0;
		}
		Node<T>* t = *p;
		*p = (*p)->next;
		delete(t);
		return 1;
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
	~LinkedList() {
		Node<T>** p;
		for (p = &head; *p; ) {
			Node<T>* t = *p;
			*p = (*p)->next;
			delete(t);
		}
	}

};

template <class T>
struct func1 {
	T operator() (T x) {
		return x * 2;
	}
};
template<class T, class R >
struct CLinkedListA :LinkedList<T, R > {
	bool insert(T x) {
		return Ins(x);
	}
	bool remove(T x) {
		return  Rem(x);
	}
	bool find(T x, Node<T>**& p) {
		return Find(x);
	}
};
template <class T, class F, class C, int N>
class HashTable {
public:
	C mat_ht[N];
	F f;
	bool Insert(T x) {
		return mat_ht[mod( f(x), N )].Insert(x);
	}
	bool Remove(T x) {
		return  mat_ht[mod(f(x), N)].Remove(x);
	}
	bool Find(T x) {
		return mat_ht[mod(f(x), N)].Find(x);
	}
	void Print() {
		for (int i = 0; i < N; i++) {
			mat_ht[i].Print();
		}
	}
};


int main() {
	HashTable<int, func1<int>,LinkedList<int, asc<int>>, 5> ht;
	ht.Insert(18);
	ht.Insert(11);
	ht.Insert(7);
    ht.Insert(3);
	ht.Insert(1);
	ht.Insert(4);
	ht.Insert(9);
	ht.Insert(5);
	ht.Print();
	cout << endl;
	ht.Remove(7);
	ht.Print();
	cout << endl;
	ht.Remove(9);
	ht.Print();

}
