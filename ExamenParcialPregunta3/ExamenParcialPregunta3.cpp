#include <iostream>
using namespace std;
void printLista(int x[], int n) {
	cout << "{ ";
	for (int i = 0; i < n - 1; i++) {
		cout << x[i] << ",";
	}
	cout << x[n - 1] << " } " << endl;
}
template <class T>
void merge(T* izq, T nIzq, T* der, T nDer, T* A) {
	T* k = A;
	T* i = izq;
	T* j = der;
	T t = *(izq + nIzq);
	*(izq + nIzq) = *izq;
	*izq = t;
	T r = *(der + nDer);
	*(der + nDer) = *der;
	*der= r;
}
template <class T>
void ordena(T* A, int *n) {
	int* a = A;
	int e = n - A;
	int* med = (a + ( e/ 2));
	if (a == med) return;
	int t = *med;
	*med= *a;
	*a = t;
	ordena<T>(A+1, med);
	ordena<T>(med,n);
}
int main()
{
	int ordenado[19] = { 90, 82, 74 ,71, 66, 62, 58, 51, 42, 38, 33, 30, 25 ,22, 17, 12, 9 ,6, 2 };
	printLista(ordenado, 19);
	ordena<int>(ordenado,ordenado+ 19);
	printLista(ordenado, 19);
}

