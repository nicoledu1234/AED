#include <iostream> 
#include <string>
#include <list> 
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
template<class G>
class Nodo
{
public:
	typedef typename G::N N;
	typedef typename G::Arista Arista;
	N n_v;
	int id;
	vector<Arista*> aristas;
	Nodo(N valor) { n_v = valor; }
};

template<class G>
class Arista
{
public:
	typedef typename G::E E;
	typedef typename G::Nodo Nodo;
	E m_v;
	Nodo* m_nodos[2];
	bool m_dir;
	Arista(E valor) { m_v = valor; }
};

template <class G>
class Cam {
public:
	typedef typename G::Nodo Nodo;
	typedef typename G::E E;
	vector<Nodo*> nodos_recorrido;
	E peso_actual;
	Cam(Nodo* actual) { nodos_recorrido.push_back(actual); peso_actual = 0; };
	void imprimir() {
		int i;
		for (i = 0; i < nodos_recorrido.size() - 1; i++) {
			cout << nodos_recorrido[i]->n_v << "-->";
		}
		cout << nodos_recorrido[i]->n_v << " " << peso_actual << endl;
	};
};


template<class N, class E>
struct  CGraph
{
	typedef CGraph<N, E> G;
	typedef Nodo<G> Nodo;
	typedef Arista<G> Arista;
	typedef N N;
	typedef E E;
	vector<Nodo*> g_node;
	bool buscar_nodo(N dato, int& pos) {
		for (int i = 0; i < g_node.size(); i++) {
			if (g_node[i]->n_v == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	
	bool buscar_arista(E dato, int indice, int& pos) {
		for (int i = 0; i < g_node[indice]->aristas.size(); i++) {
			if (g_node[indice]->aristas[i]->m_v == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	
	bool search_arista(E dato, int indice) {
		for (int i = 0; i < g_node[indice]->aristas.size(); i++) {
			if (g_node[indice]->aristas[i]->m_v == dato) {
				return 1;
			}
		}
		return 0;
	}
	
	bool insertNode(N dato) {
		int pos;
		if (buscar_nodo(dato, pos)) return 0;
		Nodo* nuevo = new Nodo(dato);
		nuevo->id = g_node.size();
		g_node.push_back(nuevo);
		return 1;
	}
	
	bool insertArista(N nodo1, N nodo2, E dato, bool direccion) {
		int actual1, actual2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (search_arista(dato, actual1) && search_arista(dato, actual2)) return 0;
		if (direccion) {
			Arista* nuevo = new Arista(dato);
			nuevo->m_dir = direccion;
			nuevo->m_nodos[0] = g_node[actual1];
			nuevo->m_nodos[1] = g_node[actual2];
			g_node[actual1]->aristas.push_back(nuevo);
			g_node[actual2]->aristas.push_back(nuevo);
			return 1;
		}
		direccion = true;
		Arista* nuevo = new Arista(dato);
		Arista* nuevo1 = new Arista(dato);
		nuevo->m_dir = direccion;
		nuevo1->m_dir = direccion;
		nuevo->m_nodos[0] = g_node[actual1];
		nuevo->m_nodos[1] = g_node[actual2];
		nuevo1->m_nodos[0] = g_node[actual2];
		nuevo1->m_nodos[1] = g_node[actual1];
		g_node[actual1]->aristas.push_back(nuevo);
		g_node[actual2]->aristas.push_back(nuevo1);
		return 1;
	}
	
	bool removeEdge(N nodo1, N nodo2, E dato) {
		int actual1, actual2, pos1, pos2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (!(buscar_arista(dato, actual1, pos1) && buscar_arista(dato, actual2, pos2))) return 0;
		g_node[actual1]->aristas.erase(g_node[actual1]->aristas.begin() + pos1);
		g_node[actual2]->aristas.erase(g_node[actual2]->aristas.begin() + pos2);
		return 1;
	}
	
	bool deleteNode(N dato) {
		int actual;
		if (!buscar_nodo(dato, actual)) return 0;
		for (int i = 0; i < g_node[actual]->aristas.size(); i++) {
			removeEdge(g_node[actual]->aristas[i]->m_nodos[0]->n_v, g_node[actual]->aristas[i]->m_nodos[1]->n_v, g_node[actual]->aristas[i]->m_v);
		}
		g_node.erase(g_node.begin() + actual);
		return 1;
	}
	
	void imprimir_nodos() {
		for (int i = 0; i < g_node.size(); i++) {
			cout << g_node[i]->n_v << " " << g_node[i]->id << endl;
		}
	}
	
	bool pos_node(Arista* arista, Nodo* actual) {
		if (arista->m_nodos[0]->n_v == actual->n_v) return 0;
		return 1;
	}
	
	void imprimir_aristas() {
		for (int i = 0; i < g_node.size(); i++) {
			for (int j = 0; j < g_node[i]->aristas.size(); j++) {
				if (!(pos_node(g_node[i]->aristas[j], g_node[i]))) {
					cout << g_node[i]->aristas[j]->m_v << ": " << g_node[i]->aristas[j]->m_nodos[0]->n_v << " " << g_node[i]->aristas[j]->m_nodos[1]->n_v << endl;
				}
			}
		}
	}
};

//===========================================================================

struct CCoord
{
	
	int m_x, m_y;

	CCoord(int x = 0, int y = 0)
	{
		m_x = x;
		m_y = y;
	}

	bool operator==(CCoord m) {
		return (m_x == m.m_x && m_y == m.m_y);
	}
	friend ostream& operator<<(ostream& os, const CCoord& dt);
	

};
ostream& operator <<(ostream& os, const CCoord& dt)
{
	os << '(' << dt.m_x << ',' << dt.m_y << ')';
	return os;
}

class CCityGraph : public CGraph<CCoord, int>
{
public:

	CCityGraph();
	typedef Cam<G> Recorrido;
	//vector<Recorrido> PathPreCalc(N nombre);
	//void PrintPath(CCoord a, CCoord b);

	
	Recorrido camino(vector<Recorrido> lerute, Nodo* actual) {
		for (int i = 0; i < lerute.size(); i++) {
			if (lerute[i].nodos_recorrido[lerute[i].nodos_recorrido.size() - 1]->n_v == actual->n_v) return lerute[i];
		}
		return Recorrido(actual);
	}
	bool bus_rec(Recorrido r, Nodo* n) {
		for (int i = 0; i < r.nodos_recorrido.size(); i++) {
			if (r.nodos_recorrido[i]->n_v == n->n_v) {
				return 1;
			}
		}
		return 0;
	}
	void nivelar(vector<Recorrido>& res) {
		bool rpta = true;
		while (rpta) {
			rpta = false;
			for (int i = 0; i < res.size(); i++) {
				for (int j = i + 1; j < res.size(); j++) {
					if (res[i].nodos_recorrido[0] == res[j].nodos_recorrido[0] && res[i].nodos_recorrido[res[i].nodos_recorrido.size() - 1] == res[j].nodos_recorrido[res[j].nodos_recorrido.size() - 1]) {
						if (res[i].peso_actual < res[j].peso_actual) {
							res.erase(res.begin() + j);
						}
						else {
							res.erase(res.begin() + i);
						}
						rpta = true;
					}
				}
			}
		}
	}
	void busqueda(vector<Recorrido>& res, Nodo* n, Arista* arista) {
		Recorrido act = camino(res, arista->m_nodos[0]);
		act.nodos_recorrido.push_back(arista->m_nodos[1]);
		act.peso_actual += arista->m_v;
		res.push_back(act);
		for (int i = 0; i < n->aristas.size(); i++) {
			if (!(pos_node(n->aristas[i], n))) {
				if (!bus_rec(act, n->aristas[i]->m_nodos[1])) {
					nivelar(res);
					busqueda(res, n->aristas[i]->m_nodos[1], n->aristas[i]);
				}
			}
		}
	}
	vector<Recorrido> PathPreCalc(N nombre) {
		vector<Recorrido> resultado;
		int pos;
		if (buscar_nodo(nombre, pos)) {
			Recorrido actual(g_node[pos]);
			resultado.push_back(actual);
			for (int i = 0; i < g_node[pos]->aristas.size(); i++) {
				if (!(pos_node(g_node[pos]->aristas[i], g_node[pos]))) {
					busqueda(resultado, g_node[pos]->aristas[i]->m_nodos[1], g_node[pos]->aristas[i]);
				}
			}
		}
		nivelar(resultado);
		imp_vec(resultado);
		return resultado;
	}
	void imp_vec(vector<Recorrido> res) {
		for (int i = 0; i < res.size(); i++) {
			res[i].imprimir();
		}
		cout << endl;
	}
	void PrintPath(CCoord a, CCoord b) {
		vector<Recorrido> rpta = PathPreCalc(a.m_x);

	}
};

CCityGraph::CCityGraph()
{}

int main(int argc, const char* argv[])
{
	CCityGraph g;
	// aqui, llenar el grafo segun la imagen de la pregunta
	g.insertNode((2, 1));
	g.insertNode((1, 1)); 
	g.insertNode((3, 2));
	g.insertNode((1, 2));
	g.insertNode((1, 3)); 
	g.insertNode((2, 4));
	g.insertNode((3, 5)); 
	g.insertNode((2, 6)); 
	g.insertNode((1, 5));
	g.insertNode((3, 3));

	g.insertArista((2, 1), (1, 1), 3, 1); 
	g.insertArista((2, 1), (3, 2), 3, 1); 
	g.insertArista((3, 2), (1, 2), 5, 1); 
	g.insertArista((3, 2), (3, 3), 3, 1);
	g.insertArista((2, 1), (1, 2), 8, 1); 
	g.insertArista((1, 2), (1, 1), 2, 1); 
	g.insertArista((1, 2), (3, 3), 9, 1); 
	g.insertArista((1, 2), (1, 3), 3, 1);
	g.insertArista((3, 3), (3, 5), 8, 1); 
	g.insertArista((3, 3), (2, 4), 5, 1); 
	g.insertArista((1, 3), (2, 4), 1, 1); 
	g.insertArista((1, 3), (1, 5), 3, 1);
	g.insertArista((2, 4), (3, 5), 4, 1);
	g.insertArista((2, 4), (1, 5), 1, 1); 
	g.insertArista((3, 5), (2, 6), 7, 1); 
	g.insertArista((2, 6), (1, 5), 3, 1);

	g.PathPreCalc(CCoord(2, 1));
	g.PrintPath(CCoord(2, 1), CCoord(2, 4));
	g.PrintPath(CCoord(2, 1), CCoord(2, 6));
	g.PathPreCalc(CCoord(1, 1));
	g.PrintPath(CCoord(1, 1), CCoord(2, 6));
	g.PrintPath(CCoord(1, 1), CCoord(3, 5));
	g.PrintPath(CCoord(2, 1), CCoord(1, 5));

	return 0;
}
