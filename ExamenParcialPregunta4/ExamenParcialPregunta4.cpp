#include <iostream>
using namespace std;

template <class T>
struct CLess
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};

template <class T>
struct CGreater
{
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

template <class T>
struct CNode
{
	CNode(T _v) { v = _v; next = 0; }
	T v;
	CNode<T>* next;
};

template <class T, class C>
class CList
{
public:
	CList();
	~CList();
	bool Find(T x, CNode<T>**& p);
	bool Insert(T x);
	bool Remove(T x);
	void Print();
	void ReverseList();
	void ReverseList1();
private:
	CNode<T>* m_head;
	C m_c;
};

template <class T, class C>
CList<T, C>::CList()
{
	m_head = 0;
}

template <class T, class C>
CList<T, C>::~CList()
{
	CNode<T>* a = m_head, * b;
	while (a)
	{
		b = a->next;
		delete a;
		a = b;
	}
}

template <class T, class C>
bool CList<T, C>::Find(T x, CNode<T>**& p)
{
	for (p = &m_head;
		*p && m_c((*p)->v, x); // (*p)->v < x
		p = &((*p)->next));
	return *p && (*p)->v == x;
}

template <class T, class C>
bool CList<T, C>::Insert(T x)
{
	CNode<T>** p;
	if (Find(x, p)) return 0;
	CNode<T>* n = new CNode<T>(x);
	n->next = *p;
	*p = n;
	return 1;
}

template <class T, class C>
bool CList<T, C>::Remove(T x)
{
	CNode<T>** p;
	if (!Find(x, p)) return 0;
	CNode<T>* t = *p;
	*p = (*p)->next;
	delete t;
	return 1;
}

template <class T, class C>
void CList<T, C>::Print()
{
	for (CNode<T>* a = m_head; a; a = a->next)
		cout << a->v << " ";
	cout << "." << endl;
}

template <class T, class C>
void CList<T, C>::ReverseList()
{
	CNode<T>* tail = m_head;
	for (; tail->next; tail = tail->next);
	CNode<T>* newHead = tail;
	while (tail!= m_head) {
		CNode<T>* a = m_head;
		for (; a != tail; a = a->next) 
			 tail->next = a;
			 tail = tail->next;
	}
	m_head->next = nullptr;
	m_head = newHead;
	
}
template <class T, class C>
void CList<T, C>::ReverseList1()
{
	CNode<T>* t0 = nullptr;
	CNode<T>* t1 = m_head;
	
	for (CNode<T>* t2 = m_head->next; t2!=nullptr; t2=t2->next) {
		t1->next = t0;
		t0 = t1;
		t1 = t2;
	}
	m_head = t1;
	t1->next = t0;
}
////////////////////////////////////////////////////////////////////////////////

int main()
{
	CList<int, CGreater<int> > l;
	l.Insert(7);
	l.Insert(2);
	l.Insert(11);
	l.Insert(8);
	l.Insert(5);
	l.Insert(18);
	l.Insert(23);
	l.Insert(17);
	l.Insert(26);
	l.Print();
	l.ReverseList1();
	l.Print();
}