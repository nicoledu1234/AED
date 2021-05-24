#include <iostream>
#include <string>
using namespace std;

template <class R>
void swap(R* a, R* b) {
	R copia = *a;
	*a = *b;
	*b = copia;
}
template <class R>
void imprimirArray(R* ini, int  tam) {
	for (R* i = ini; i < ini + tam - 1; i++) {
		cout << *(i) << ", ";
	}
	cout << *(ini + tam - 1) << endl;
}
template <class R>
class Par {
public:
	bool operator()(R a) {
		return !(a & 1);
	}
};

template <class R>
int modulo(R t, R m) {
	int mo = -1;
	if (t < 0)
		return (t * mo >= m) ? (t - (t / m * m)) + m : t + m;
	return (t >= m) ? t - (t / m * m) : t;
}
template <class R>
class Multiplo3 {
public:
	bool operator()(R a) {
		return !modulo(a, 3);
	}
};
template <class R>
class Multiplo5 {
public:
	bool operator()(R a) {
		return !modulo(a, 5);
	}
};

template <class T, class R>
class Split {
public:
	T comp;
	void operator()(R* arr, R* q, int tam) {
		R* r = nullptr;
		q = nullptr;
		//T comp;
		for (R* p1 = arr; p1 < arr + tam; p1++) {
			if (comp(*p1)) {
				if (!q) {
					q = p1;
				}
			}
			else {
				if (!q) {
					q = arr;
				}
				else {
					swap<R>(p1, q);
					if (q != p1) {
						r = q;
						while (r != p1) {
							swap<R>(r, p1);
							r++;
						}
					}
					q++;
				}
			}
		}
	}

};

int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	imprimirArray<int>(arr, 10);
	int* q = nullptr;
	Split<Par<int>, int> sp;
	sp(arr, q, 10);
	cout << "Pares" << endl;
	imprimirArray<int>(arr, 10);
	cout << endl;

	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
	imprimirArray<int>(arr1, 10);
	int* r = nullptr;
	Split<Multiplo3<int>, int> sp3;
	sp3(arr1, r, 10);
	cout << "Multiplos de 3" << endl;
	imprimirArray<int>(arr1, 10);
	cout << endl;

	int arr2[] = { 1,2,3,4,5,6,7,8,9,10 };
	imprimirArray<int>(arr2, 10);
	Split<Multiplo5<int>, int>sp2;
	int* t = nullptr;
	sp2(arr2, t, 10);
	cout << "Multiplos de 5" << endl;
	imprimirArray<int>(arr2, 10);
	cout << endl;

}