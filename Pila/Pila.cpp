#include <iostream>

using namespace std;


template<class T>
class Node {
	public:
		T value;
		Node* next;
		Node(T v, Node* n) {
			value = v;
			next = n;
		}
};

template<class T>
	class Pila {
	private:
		Node<T>* head;
	public:
		Pila() {
			head = nullptr;
		}
	
		bool Push(T x) {
			head = new Node<T>(x, head);
			return 1;
		}
		T Pop() {
			if (!head) {
				cout << "Empty Pila" << endl;
				return 0;
			}
			Node<T>* temp = head;
			T r = head->value;
			head = head->next;
			delete temp;
			return r;
		}
		~Pila() {
			Node<T>** p;
			for (p = &head; *p; ) {
				Node<T>* t = *p;
				*p = (*p)->next;
				delete(t);
			}
		}
		void Print() {
			if (!head) {
				cout << "Empty Pila" << endl;
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
	cout << "Pila " << endl;
	Pila<int> pila;
	bool interfaz = true;
	char opcion;
	while (interfaz) {
		cout << "Elige una opcion: "<<endl;
		cout << "  1 = Push" << endl;
		cout << "  2 = Pop" << endl;
		cout << "  3 = Salir" << endl;
		cin >> opcion;

		switch (opcion) {
		case '1':
			int numero;
			cout << "Que numero desea ingresar a la pila: ";
			cin >> numero;
			pila.Push(numero);
			pila.Print();
			break;

		case '2':
			pila.Pop();
			pila.Print();
			break;

		case '3':
			pila.~Pila();
			pila.Print();
			interfaz = false;
			break;
		}
	}
}