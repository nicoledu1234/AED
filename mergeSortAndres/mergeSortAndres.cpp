#include <iostream>
#include <ctime>
using namespace std;



// Print
void Print(int* a, int tam) {
	cout << "{ ";
	for (int* b = a; b < a + tam; b++)
		if (b < (a + tam) - 1) {
			cout << *b << " , ";
		}
		else {
			cout << *b << " }";
		}
	cout << endl;
}


// Merge
void Merge(int* a, int* left, int* right, int sl, int sr) {

	int* k = a;
	int* j = right;
	int* i = left;

	while ((i < left + sl) && (j < right + sr)) {
		if (*i <= *j) {
			*k = *i;
			i++;
		}
		else {
			*k = *j;
			j++;
		}
		k++;
	}

	while (i < left + sl) {
		*k = *i;
		i++;
		k++;
	}
	while (j < right + sr) {
		*k = *j;
		j++;
		k++;
	}
}


// MergeSort
void MergeSort(int* a, int tam) {

	// Calculate half of the size
	int n = tam / 2;
	// If the array has one element is sorted
	if (tam < 2) {
		return;
	}

	// Create 2 arrays
	int* left = new int[n];
	int* right = new int[tam - n];

	// Fill the arrays
	int* k = a ;
	for (int* i = left; i < left + n; i++) {
		*i = *k;
		k++;
	}
	int* r = a+ n;
	for (int* j = right; j < right + (tam - n); j++) {
		*j = *r;
		r++;
	}

	// Recall
	MergeSort(left, n);
	MergeSort(right, (tam - n));
	Merge(a, left, right, n, (tam - n));
	//delete[] left;
   //delete[] right;
}

int mod(int x, int y) {
	if (x >= 0)return x - (x / y) * y;
	return x - ((x / y) - 1) * y;
}


// Main
int main() {
	int tam = 10;
	int* array = new int[tam];

	// Rellenando el Array
	//srand(time(NULL));
	int aleatorio;
	for (int* i = array; i < array + tam; i++) {
		aleatorio = mod(rand(), (tam - 0 + 1) + 1);
		*i = aleatorio;
	}


	unsigned t0, t1;
	t0 = clock();
	cout << "Initial Array" << endl;
	Print(array, tam);
	cout << "Final Array" << endl;
	MergeSort(array, tam);
	Print(array, tam);

	// Time
	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;

	delete[] array; 
}