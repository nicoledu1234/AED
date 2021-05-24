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
		Node* prev;
		Node(T v, Node* n = nullptr, Node* p = nullptr) {
			value = v;
			next = n;
			prev = p;
		}
};
template<class T, class R>
class LinkedList {
	private:
		Node<T>* head;
		Node<T>* tail;
		R r;
	public:
		LinkedList() {
			head = nullptr;
			tail = nullptr;
		}
		bool Find(T value, Node<T>**& n, Node<T>*& p) {
			n = &head; p = head ;

			if (*n) {
				if (r((*n)->value , value)) n = &((*n)->next);
				for (; r((*n)->value, value) && (*n != head); p = *n, n = &((*n)->next));
				if ((*n)->value == value) return 1;
			}

			return 0;
		}
		bool Insert(T x) {
			Node<T>** n=nullptr;
			Node<T>* p=nullptr;
			if (Find(x,n, p)) {
				return 0;
			}
			
			*n = new Node<T>(x, *n, p);
			if(!head->next){
				(*n)->prev = *n;
				(*n)->next = *n;
			}
			else if (*n==head) {
				Node<T>** last = &head->next->prev;
				(*n)->prev = *last;
				(*last)->next = *n; 
				(*n)->next->prev = *n;
			}
			else {
				(*n)->next->prev = *n;
			}
			return 1;
		}
		bool Remove(T x) {
			Node<T>** n=nullptr;
			Node<T>* p=nullptr;
			if (!Find(x,n, p)) {
				return 0;
			}
			Node<T>* temp = *n;
			*n = (*n)->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			if (temp == head) { head = nullptr; }
			delete temp;
			return 1;
		}
		void Josephus(int n, int k) {
			for (int i = 1; i <= n; i++) {
				Insert(i);
			}
			Print();
			int j = 1;
			Node<T>* i = head;
			while(head){
				if (j == k) {
					j = 1;
					cout << i->value << endl;
					Node<T>* temp = i;
					i = i->next; Remove(temp->value);
				}
				++j;
				if(n!=1) i = i->next;
			}
		}
		void Print() {
			if (!head) {
				cout << "Empty " << endl;
			}
			else {
				cout << "<-";
				cout << head->value << "<=>";
				Node<T>* i = head->next;
				for (; i!=head; i = i->next) {
					cout << i->value << "<=>";
				}
				cout <<endl;

			}
		}

};
int main() {
	cout << "Lista Enlazada Simple" << endl; 
	cout << "  1 = Ascendente" << endl;
	cout << "  2 = Descendente" << endl;
	char orden; 
	cin >> orden;
	if (orden == 1) {
		LinkedList<int, asc<int>> listaA;
		bool interfaz = true;
		char opcion;
		while (interfaz) {
			cout << "Elige una opcion: " << endl;
			cout << "  1 = Push" << endl;
			cout << "  2 = Pop" << endl;
			cout << "  3 = Josephus" << endl;
			cout << "  4 = Salir" << endl;
			cin >> opcion;
			switch (opcion) {
			case '1':
				int numero;
				cout << "Que numero desea ingresar a la Lista: ";
				cin >> numero;
				listaA.Insert(numero);
				listaA.Print();
				break;

			case '2':
				int num;
				cout << "Que numero desea eliminar de la Lista: ";
				cin >> num;
				listaA.Remove(num);
				listaA.Print();
				break;

			case '3':
				int n;
				cout << "Para resolver el Problema de Josephus, cuantos soldados tiene:";
				cin >> n;
				int k;
				cout << "Cada cuantos mueren:";
				cin >> k;
				listaA.Josephus(n, k);
				break;
			case '4':
				interfaz = false;
				break;
			}
		}
	}
	else{
		LinkedList<int, asc<int>> listaB;
		bool interfaz = true;
		char opcion;
		while (interfaz) {
			cout << "Elige una opcion: " << endl;
			cout << "  1 = Push" << endl;
			cout << "  2 = Pop" << endl;
			cout << "  3 = Josephus" << endl;
			cout << "  4 = Salir" << endl;
			cin >> opcion;
			switch (opcion) {
			case '1':
				int numero;
				cout << "Que numero desea ingresar a la Lista: ";
				cin >> numero;
				listaB.Insert(numero);
				listaB.Print();
				break;

			case '2':
				int num;
				cout << "Que numero desea eliminar de la Lista: ";
				cin >> num;
				listaB.Remove(num);
				listaB.Print();
				break;

			case '3':
				int n;
				cout << "Para resolver el Problema de Josephus, cuantos soldados tiene:";
				cin >> n;
				int k;
				cout << "Cada cuantos mueren:";
				cin >> k;
				listaB.Josephus(n, k);
				break;
			case '4':
				interfaz = false;
				break;
			}
		}
	}
	
	return 0;
}

	