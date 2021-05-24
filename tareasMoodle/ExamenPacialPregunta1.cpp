#include <iostream>
using namespace std;
class Node {
public:
	int value;
	Node* next;
	int status;
	Node(int v, Node* n) {
		value = v;
		next = n;
		status = 0;
	}
};

class Pila {
public:
	Node* head;
	Pila() {
		head = nullptr;
	}

	bool Push(int x) {
		if (!head) {
			head = new Node(x, head);
			return 1;
		}
		if (x == head->value) {
			head->status++;
			return 1;
		}
		head = new Node(x, head);
		return 1;
	}
	int headStatus() {
		return head->status;
	}
	int Pop() {
		if (!head) {
			cout << "Empty Pila" << endl;
			return 0;
		}
		if (head->status != 3) return 0;
		Node* temp = head;
		int r = head->value;
		head = head->next;
		delete temp;
		return r;
	}
	~Pila() {
		Node** p;
		for (p = &head; *p; ) {
			Node* t = *p;
			*p = (*p)->next;
			delete(t);
		}
	}
	void Print() {
		if (head->status == 1)
			cout << head->status << "  ";

	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
	CBinNode(int _v){
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
	void PrintLevelX(int x);
	void PrintRange(int from, int to);
	void PrintOneChildNodes();

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

void CBinTree::PrintLevelX(int x)
{
	cout << "\nLevel: " << x << endl;
	//...
}

void CBinTree::PrintRange(int from, int to)
{
	Pila pila;
	CBinNode** q;
	Find(from, q);
	while (!Find(from, q)) {
		from++;
	}
	pila.Push((*q)->value);
	cout <<  (*q)->value<<" ";
	CBinNode* p = *q;
	p = p->nodes[1];
	while (pila.head && p) {
		pila.Push(p->value);
		int status = pila.headStatus();
		if (status == 0) {
			if (p->nodes[0] == nullptr) continue;
			p = p->nodes[0];
		}
		else if (status == 1) {
			if (p->value <= to) {
				cout << p->value << "  ";
			}
			if (p->nodes[0] == nullptr) continue;
		}
		else if (status == 2) {
			if (p->nodes[1] == nullptr) continue;
			p = p->nodes[1];
		}
		else {
			pila.Pop();
			if (pila.head) {
				CBinNode** q;
				Find(pila.head->value, q);
				p = *q;
			}

		}
		
	}
	cout << endl;

}

void CBinTree::PrintOneChildNodes(void)
{
	Pila pila;
	pila.Push(m_root->value);
	CBinNode* p = m_root;
	p = p->nodes[0];
	while (pila.head && p) {
		pila.Push(p->value);
		int status = pila.headStatus();
		if (status == 0) {
			if (p->nodes[0] == nullptr) continue;
			p = p->nodes[0];
		}
		else if (status == 1) {
			if((p->nodes[0]&& !p->nodes[1])|| (!p->nodes[0] && p->nodes[1])) cout << p->value << "  ";
			if (p->nodes[0] == nullptr) continue;
		}
		else if (status == 2) {
			if (p->nodes[1] == nullptr) continue;
			p = p->nodes[1];
		}
		else {
			pila.Pop();
			if (pila.head) {
				CBinNode** q;
				Find(pila.head->value, q);
				p = *q;
			}

		}
	}
	cout << endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	CBinTree t;

	t.Insert(47); t.Insert(15); t.Insert(83); t.Insert(59); t.Insert(36); t.Insert(44); t.Insert(41);
	t.Insert(75); t.Insert(62); t.Insert(7); t.Insert(21); t.Insert(65); t.Insert(85); t.Insert(4);
	t.Insert(97); t.Insert(47); t.Insert(87); t.Insert(56); t.Insert(42); t.Insert(32); t.Insert(13);
	t.PrintLevelX(0);
	t.PrintLevelX(1);
	t.PrintLevelX(2);
	t.PrintLevelX(3);
	t.PrintLevelX(4);
	t.PrintRange(20, 75);
	t.PrintRange(56, 97);
	t.PrintRange(2, 30);
	t.PrintOneChildNodes();
}