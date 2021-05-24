#include <iostream>
using namespace std;

template<class T>
class Node{
	public:
		T value;
		int x, y;
		Node* Hnext;
		Node* Vnext;

		Node(T v,int x_,int y_) {
			value = v;
			x = x_;
			y = y_;
			Hnext = NULL;
			Vnext = NULL;
		}
};

template<class T>
class SparseMatrix {
	private:
		int rows;
		int columns;
		Node<T>** H ;
		Node<T>** V ;

	public:
		SparseMatrix(int a, int b) {
			rows = a;
			columns = b;
			H = new Node<T> * [rows];
			V = new Node<T> * [columns];
			int max = a > b ? a : b;
			for (int i = 0; i < max; i++) {
				H[i] = nullptr;
				for (int j = 0; j < max; j++) {
					V[j] = nullptr;
				}
			}
		}
		
		T Find(int a, int b, Node<T>**& p, Node<T>**& q) {
			for (q = &H[a]; *q && (*q)->y < b; q = &((*q)->Vnext));
			for (p = &V[b]; *p && (*p)->x < a; p = &((*p)->Hnext));
			return *p && *q && *p == *q ? (*p)->value : 0;
		}
		
		bool Insert(T x, int a, int b) {
			if (a >= rows || b >= columns) {
				cout << "Parametro Fuera de la matriz" << endl;
				return 0;
			}
			Node<T>** p;
			Node<T>** q;
			if (Find(a, b, p, q)) {
				return 0;
			}
			Node<T>* n = new Node<T>(x,a,b);
			n->Hnext = *p;
			n->Vnext = *q;
			*p = n;
			*q = n;
			return 1;
		}
		
		bool Set(T x, int a, int b) {
			if (a >= rows || b >= columns) {
				cout << "Parametro Fuera de la matriz" << endl;
				return 0;
			}
			if (x == 0) {
				Remove(a, b);
				return 0;
			}
			Node<T>** p;
			Node<T>** q;
			if (!Find(a, b, p, q)) {
				Node<T>* n = new Node<T>(x,a,b);
				n->Hnext = *p;
				n->Vnext = *q;
				*p = n;
				*q = n;
				return 1;
			}
			(*p)->value = x;
			return 1;
		}
		
		bool Remove(int a,int b) {
			if (a >= rows || b >= columns) {
				cout << "Parametro Fuera de la matriz" << endl;
				return 0;
			}
			Node<T>** p;
			Node<T>** q;
			if (!Find(a, b, p, q)) {
				return 0;
			}
			Node<T>* t = *p;
			Node<T>* t1 = *q;
			*p = (*p)->Hnext;
			*q = (*q)->Vnext;
			delete(t);
			return 1;
		
		}
		
		bool Transpose() {
			Node<T>** p;
			Node<T>** q;
			Node<T>** t;
			Node<T>** r;
			for (int f = 0; f < rows; f++) {
				for (int c = f+1; c < columns; c++) {
					T tmp = Find(f, c, p, q);
					T tmp1 = Find(c, f, t, r);
					Set(tmp, c, f);
					Set(tmp1, f, c);
				}
			}
			int tm = rows;
			rows = columns;
			columns = tm;
			return 1;
		}

		void Print() {
			Node<T>** p;
			Node<T>** q;
			cout << "Impresion como coordenadas:" << endl;
			for (int f = 0; f < rows; f++) { 
				for (int c = 0; c < columns; c++) {
					if(Find(f, c, p, q)!=0) cout <<" ( "<< (*p)->x << " , "<< (*p)-> y<<" ) = "<< (*p)->value << endl;
				}
			}
			cout << endl;
		}

		void PrintMatrix() { 
			Node<T>** p; 
			Node<T>** q;
			cout << "Impresion como matriz:" << endl;
			for (int f = 0; f < rows; f++) {
				for (int c = 0; c < columns; c++) cout << Find(f, c, p, q) << "   "; 
				cout << endl;
			}
			cout << endl;
		}
		~SparseMatrix() {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					delete V[j];
				}
				delete H[i] ;
			}
		}
		
};

int main()
{
	
	cout << "------ SPARSE MATRIX -------" << endl;
	cout << "Ingrese el tamaño de su matriz" << endl;
	cout << "Filas:";
	int fil;
	cin >> fil;
	cout << "Colummnas:";
	int col;
	cin >> col;
	SparseMatrix<int> mat(fil, col);
	cout << endl;
	cout << "  1 = Insert" << endl;
	cout << "  2 = Set" << endl;
	cout << "  3 = Remove" << endl;
	cout << "  4 = Find" << endl;
	cout << "  5 = Transpose" << endl;
	cout << "  6 = Print coordenates" << endl;
	cout << "  7 = Print Matrix" << endl;
	cout << "  0 = Finish" << endl;
	cout << endl;

	bool code = true;
	int tecla;
	while (code) {
		cout << endl;
		cout << "- Chose an a option: ";
		cin >> tecla;
		cout << endl;

		switch (tecla) {
		case 1:
			int numero;
			int fil;
			int col;
			cout << "Insert: "<<endl;
			cout << "Numero: " << endl;
			cin >> numero;
			cout << "Fila: " << endl;
			cin >> fil;
			cout << "Colummna: " << endl;
			cin >> col;
			mat.Insert(numero,fil,col);
			break;

		case 2:
			int numero1;
			int fil1;
			int col1;
			cout << "Set: " << endl;
			cout << "Numero: " << endl;
			cin >> numero1;
			cout << "Fila: " << endl;
			cin >> fil1;
			cout << "Colummna: " << endl;
			cin >> col1;
			mat.Set(numero1, fil1, col1);
			break;

		case 3:
			int fil2;
			int col2;
			cout << "Remove: " << endl;
			cout << "Fila: " << endl;
			cin >> fil2;
			cout << "Colummna: " << endl;
			cin >> col2;
			mat.Remove(fil2, col2);
			break;

		case 4:
			int fil3;
			int col3;
			Node<int>** p;
			Node<int>** q;
			cout << "Find: " << endl;
			cout << "Fila: " << endl;
			cin >> fil3;
			cout << "Colummna: " << endl;
			cin >> col3;
			cout<< mat.Find(fil3, col3,p ,q)<<endl;
			break;

		case 5:
			cout << "Transpose Matrix:" << endl;
			mat.Transpose();
			mat.PrintMatrix();
			break;

		case 6:
			mat.Print();
			break;

		case 7:
			mat.PrintMatrix();
			break;

		case 0:
			code = false;
			break;
		}
	}

}
