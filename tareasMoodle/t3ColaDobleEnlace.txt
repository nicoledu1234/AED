#include <iostream>

using namespace std;


template<class T>
class Node {
	public:
		T value;
		Node* next;
		Node* prev;
		Node(T v, Node* n=nullptr, Node* p=nullptr) {
			value = v;
			next = n;
			prev = p;
		}
};
template<class T>
class Cola {
	private:
		Node<T>* head;
		Node<T>* tail;
	public:
		Cola() {
			head = nullptr;
			tail = nullptr;
		}

		bool Push(T x) {
			if (!head) {
				head = new Node<T>(x, head,nullptr);
				tail = head;
				return 1;
			}
			tail->next = new Node<T>(x,tail->next,tail);
			tail = tail->next;
			return 1;
		}
		T Pop() {
			if (!head) {
				cout << "Empty Cola" << endl;
				return 0;
			}
			Node<T>* temp = head;
			T r = head->value;
			head = head->next;
			if (head)  head->prev = NULL;
			delete temp;
			return r;
		}
		~Cola() {
			Node<T>** p;
			for (p = &head; *p; ) {
				Node<T>* t = *p;
				*p = (*p)->next;
				delete(t);
			}
		}
		void Print() {
			if (!head) {
				cout << "Empty Cola" << endl;
			}
			else {
				cout << "||<-" ; 
				Node<T>* i = head;
				for (; i&& i->next; i = i->next) {
					cout << i->value << "<=>";
				}
				cout << i->value << "->";
				cout << "|| " << endl;
			}

		}

};

int main() {
	cout << "Cola " << endl;
	Cola<int> cola;
	bool interfaz = true;
	char opcion;
	while (interfaz) {
		cout << "Elige una opcion: " << endl;
		cout << "  1 = Push" << endl;
		cout << "  2 = Pop" << endl;
		cout << "  3 = Salir" << endl;
		cin >> opcion;

		switch (opcion) {
		case '1':
			int numero;
			cout << "Que numero desea ingresar a la cola: ";
			cin >> numero;
			cola.Push(numero);
			cola.Print();
			break;

		case '2':
			cola.Pop();
			cola.Print();
			break;

		case '3':
			cola.~Cola();
			cola.Print();
			interfaz = false;
			break;
		}
	}
}