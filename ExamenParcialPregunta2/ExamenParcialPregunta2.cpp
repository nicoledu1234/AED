#include <iostream>
#include <stack>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
	CBinNode(int _v)
	{
		value = _v; nodes[0] = nodes[1] = 0;
	}
	int value;
	CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
	CBinTree();
	~CBinTree();
	bool Insert(int x);
	bool Remove(int x);
	void Print();
	void StackBasedPrint();
private:
	bool Find(int x, CBinNode**& p);
	CBinNode** Rep(CBinNode** p);
	void InOrder(CBinNode* n);
	CBinNode* m_root;
};

CBinTree::CBinTree()
{
	m_root = 0;
}

CBinTree::~CBinTree()
{}

bool CBinTree::Find(int x, CBinNode**& p)
{
	for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
	return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
	CBinNode** p;
	if (Find(x, p)) return 0;
	*p = new CBinNode(x);
	return 0;
}
bool CBinTree::Remove(int x)
{
	CBinNode** p;
	if (!Find(x, p)) return 0;
	if ((*p)->nodes[0] && (*p)->nodes[1])
	{
		CBinNode** q = Rep(p);
		(*p)->value = (*q)->value;
		p = q;
	}
	CBinNode* t = *p;
	*p = (*p)->nodes[!(*p)->nodes[0]];
	delete t;
	return 1;
}

CBinNode** CBinTree::Rep(CBinNode** p)
{
	bool b = rand() % 2;
	for (p = &((*p)->nodes[b]); (*p)->nodes[!b]; p = &((*p)->nodes[!b]));
	return p;
}

void CBinTree::InOrder(CBinNode* n)
{
	if (!n) return;
	InOrder(n->nodes[0]);
	cout << n->value << " ";
	InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
	InOrder(m_root);
	cout << endl;
}

void CBinTree::StackBasedPrint()
{
	stack<CBinNode*>pila;
	CBinNode* p = m_root;
	while (p  || !pila.empty()) {
		while (p) {
			pila.push(p);
			p = p->nodes[1];
		}
		p = pila.top();
		pila.pop();
		cout << p->value << " ";
		p = p->nodes[0];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	CBinTree t;

	t.Insert(47); t.Insert(15); t.Insert(83); t.Insert(59); t.Insert(36); t.Insert(44); t.Insert(41);
	t.Insert(75); t.Insert(62); t.Insert(7); t.Insert(21); t.Insert(65); t.Insert(85); t.Insert(4);
	t.Insert(97); t.Insert(47); t.Insert(87); t.Insert(56); t.Insert(42); t.Insert(32); t.Insert(13);
	t.Print();
	t.StackBasedPrint();
}