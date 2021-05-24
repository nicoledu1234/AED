#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ctime> 

using namespace std;

template<class T>
T mod(T t, T m) {
	T mo = -1;
	if (t < 0)
		return (t * mo >= m) ? (t - (t / m * m)) + m : t + m;
	return (t >= m) ? t - (t / m * m) : t;
}
template <class T>
void printLista(T x[], int n) {
	cout << "{ ";
	for (int i = 0; i < n - 1; i++) {
		cout << x[i] << ",";
	}
	cout << x[n - 1] << " } " << endl;
}
template <class T>
struct Comparar{
	virtual bool comparar(T, T) = 0;
};
template <class T>
struct Ascendente:Comparar<T> {
    bool comparar(T a, T b) {
		return a < b;
	}
};
template <class T>
struct Descendente :Comparar<T> {
	bool comparar(T a, T b) {
		return a > b;
	}
};

template <class T>
void merge(T* izq, T nIzq, T* der, T nDer, T* A, Comparar<T>*comp) {
	T* k = A;
	T* i = izq;
	T* j = der;
	while ((i < izq + nIzq) && (j < der + nDer)) {
		if (comp->comparar(*i, *j)) {
			*k = *i;
			i++;
		}
		else {
			*k = *j;
			j++;
		}
		k++;
	}
	while (i < izq + nIzq) {
		*k = *i;
		i++; k++;
	}
	while (j < der + nDer) {
		*k = *j;
		j++; k++;
	}
}
template <class T>
void mergeSort(T* A, int n, Comparar<T> *comp ) {
	if (n == 1) {
		return;
	}
	int mitad = n / 2;
	T* izq = new T[mitad];
	T* der = new T[n - mitad];
	T* k = A;
	for (T* i = izq; i < izq + mitad; i++) {
		*i = *k;
		k++;
	}
	T* r = A + mitad;
	for (T* j = der; j < der + (n - mitad); j++) {
		*j = *r;
		r++;
	}

	mergeSort<T>(izq, mitad, comp);
	mergeSort<T>(der, n - mitad, comp);
	merge<T>(izq, mitad, der, n - mitad, A, comp);
}
int main() {
	int tam = 4000000;
	int* lista = new int[tam];

	int aleatorio;
	for (int* i = lista; i < lista + tam; i++) {
		aleatorio = mod(rand(), (tam - 0 + 1) + 1);
		*i = aleatorio;
	}
	//printLista<int>(lista, tam);
	Ascendente<int> a;
	Comparar<int>* comp;
	comp=&a;

	unsigned t0, t1;
	t0 = clock();
	mergeSort<int>(lista, tam, comp);

	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
	delete[] lista;
	return 0;
}