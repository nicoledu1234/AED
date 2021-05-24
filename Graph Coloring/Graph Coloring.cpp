#include <iostream> 
#include <string>
#include <list> 
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int mod(int x, int y) {
	if (x >= 0)return x - (x / y) * y;
	return x - ((x / y) - 1) * y;
}

int generadorAleatorios(int maximo) {
	srand(time(NULL));
	int aleatorio, DESDE = 0, HASTA = maximo-1;
	aleatorio = mod(rand(), (HASTA - DESDE + 1) + DESDE);
	return aleatorio;
}

int factorial(int x) {
	if (x == 0 || x == 1) return x;
	return x* factorial(x - 1);
}
template< class N , class E>
struct  Graph {
	struct Node;

	struct Edge {
		E edge_value;
		bool dir;  /// 0 <-> | 1 ->
		Node* nodes[2]; /// 0-> inicio | 1-> llegada

		Edge(Node* a, Node* b, E value, bool d) {
			edge_value = value;
			nodes[0] = a;
			nodes[1] = b;
			dir = d;
		}

		~Edge() {
			// delete[] nodes;
		}
	};

	struct  Node {
		N node_value;
		list<Edge*> edges; /// lista de edges del nodo
		bool colored=0;
		int color=0;

		Node(N value) {
			node_value = value;
		}

		~Node() {
			//edges.~list;
		}
	};
	
	int GraphSize=0;
	list<Node*> nodes;

	bool InsertNode(N value) {
		Node* a= new Node(value);
		nodes.push_back(a);
		GraphSize++;
		return 1;
	}

	bool RemoveNode(N a) {
		auto nodeA = find_if(nodes.begin(), nodes.end(),
			[&a]( Node*& i_nodeA) {
				return i_nodeA->node_value == a;
			}
		);
		if (nodeA == nodes.end()) {
			cout << "Invalid Node" << endl;
			return 0;
		}
		auto it = (*nodeA)->edges.begin();
		for (; it != (*nodeA)->edges.end(); ++it) {
			Edge* e = *it;
			Edge* e1 = *it;
			if (e->nodes[0] == (*nodeA)) e->nodes[1]->edges.remove(e);
			else if (e1->nodes[1] == (*nodeA)) e1->nodes[0]->edges.remove(e1);
		}
		//Edge* a = *it;
		//(*nodeA)->edges.remove(a);
		nodes.remove((*nodeA));
		GraphSize--;
		return 1;
	}

	bool InsertEdge(N a, N b, E  value, bool d) {
		///Busco el nodo con valor A
		auto nodeA = find_if(nodes.begin(), nodes.end(),
			[&a](Node*& i_nodeA) {
				return i_nodeA->node_value == a;
			}
		);
		if (nodeA == nodes.end()) {
			cout << "Invalid Node" << endl;
			return 0;
		}
		///Busco el nodo con valor  B
		auto nodeB = find_if(nodes.begin(), nodes.end(),
			[&b](Node*& i_nodeB) {
				return i_nodeB->node_value == b;
			}
		);
		if (nodeB == nodes.end()) {
			cout << "Invalid Node" << endl;
			return 0;
		}
		Edge* e= new Edge((*nodeA), (*nodeB), value, d);
		(*nodeA)->edges.push_back(e);
		(*nodeB)->edges.push_back(e);
		return 1;
	}

	bool RemoveEdge(N a, N b, E value) {
		///Busco el nodo con valor A
		auto nodeA = find_if(nodes.begin(), nodes.end(),
			[&a]( Node*& i_nodeA) {
				return i_nodeA->node_value == a;
			}
		);
		if (nodeA == nodes.end()) {
			cout << "Invalid Node" << endl;
			return 0;
		}
		///Busco el nodo con valor  B
		auto nodeB = find_if(nodes.begin(), nodes.end(),
			[&b]( Node*& i_nodeB) {
				return i_nodeB->node_value == b;
			}
		);
		if (nodeB == nodes.end()) {
			cout << "Invalid Node" << endl;
			return 0;
		}
		///Busco el edge con valor value y que termine en B en en la lista de edges de  A
		auto edge = find_if((*nodeA)->edges.begin(), (*nodeA)->edges.end(),
			[&value, &nodeB]( Edge*& i_edgeA) {
				bool r = i_edgeA->edge_value == value;
				bool t = (i_edgeA->dir == 0? i_edgeA->nodes[1] == *nodeB || i_edgeA->nodes[0] == *nodeB : i_edgeA->nodes[1] == *nodeB);
				return (r &&t );
			}
		);
		if (edge == (*nodeA)->edges.end()) {
			cout << "Invalid edge 1" << endl;
			//return 0;
		}
		auto edgeB = find_if((*nodeB)->edges.begin(), (*nodeB)->edges.end(),
			[&value, &nodeA](Edge*& i_edgeA) {
				bool r = i_edgeA->edge_value = value;
				bool t = (i_edgeA->dir == 0 ? i_edgeA->nodes[1] == *nodeA || i_edgeA->nodes[0] == *nodeA : i_edgeA->nodes[0] ==  *nodeA);
				return (r && t);
			}
		);
		if (edgeB == (*nodeB)->edges.end()) {
			cout << "Invalid edge" << endl;
			//return 0;
		}
	
		(*nodeA)->edges.erase(edge);
		(*nodeB)->edges.erase(edgeB);


		return 1;
	}
	
	list<Node*> createPermutation(vector< list<Node*> > orders) {
		int aleatorio = generadorAleatorios(orders.size());
		list<Node*> nodes_ = orders[aleatorio];
		vector <int> orden;
		for (int i = 0; i < GraphSize; i++) orden.push_back(i);
		for (int i = 0; i < GraphSize/2; i++) {
			int aleatorio = generadorAleatorios(GraphSize);
			int temp = orden[i];
			orden[i] = orden[aleatorio];
			orden[aleatorio] = temp;
		}
		list<Node*> tempPerm;
		for (int i = 0; i< GraphSize; i++) {
			int max = orden[i];
			int cont = 0;
			typename list<Node*>::iterator it = nodes_.begin();
			for (; cont != max ; ++it,cont ++);
			 tempPerm.push_back(*it);
		}
		return tempPerm;
	}

	bool checkRep(vector< list<Node*> > orders, list<Node*> tempPerm) {
		for (auto r = orders.begin(); r != orders.end(); ++r) {
			int contRep = 0;
			list<Node*> tm = *r;
			typename list<Node*>::iterator a = tempPerm.begin();
			for (typename list<Node*>::iterator it = tm.begin(); it != tm.end(); ++it, ++a) {
				if ((*it)->node_value == (*a)->node_value) contRep++;
			}
			if(contRep == GraphSize ) return true ;
		}
		return false;
	}

	void createOrders(list<Node*> nodes, vector< list<Node*> > *orders) {
		int maximo = factorial(GraphSize);
		if (maximo > 100) maximo = 100;
		for (int i = 1; i < maximo; ) {
			list<Node*> temp = createPermutation(*orders);
			if (checkRep(*orders, temp) == false) {
				orders->push_back(temp);
				i++;
			}	
		}
	}

	list<Node*> colorOptions( vector< list<Node*> > orders) {
		list<Node*> bestOrder=orders[0];
		int minColores = Coloring(bestOrder);
		auto r = orders.begin();
		r++;
		for (; r != orders.end(); ++r) {
			int t = Coloring(*r);
			if (t < minColores) {
				minColores = t;
				bestOrder = *r;
			}
		}
		return bestOrder;
	}
	bool colRep(vector<int>colors, int x) {
		int tam = colors.size();
		for (int i = 0; i < tam; i++) {
			if (colors[i] == x) return false;
		}
		return true;
	}
	void GraphColoring() {
		vector< list<Node*> > orders;
		orders.push_back(nodes);
		vector< list<Node*> >* ptr = &orders;
		createOrders(nodes, ptr);
		list<Node*> best = colorOptions(orders);
		int maxC= Coloring(best);
		nodes = best;
		vector<int>colors;
		cout << "Best Coloring:" << endl;
		for (typename list<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			cout << "Nodo " << (*it)->node_value << " -> Color " << (*it)->color << endl;
			if(colRep(colors, (*it)->color) == true ) colors.push_back((*it)->color);
		}
		cout << "Colores usados: " << maxC << endl;
		sort(colors.begin(), colors.end());

		cout << "Colors:" << endl;
		for (auto r = colors.begin(); r != colors.end(); ++r) {
			cout << "Color " << *r << " , ";
		}
		cout << endl;
	}
	int cantColores(list<Node*> nodes) {
		int numColores = 0;
		vector<int> colores;
		for (typename list<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			int co = (*it)->color;
			bool rep = false;
			for (auto r = colores.begin(); r != colores.end(); ++r) {
				if (*r == co) rep = true;
			}
			if (rep == false) colores.push_back(co);
		}
		numColores = colores.size();
		return numColores;
	}

	int menColor(vector<int>& v) {
		sort(v.begin(), v.end());
		int t = 1;
		for (auto r = v.begin(); r != v.end(); ++r) {
			if (t != *r) return t;
			t++;
		}
		return t;
	}

	// Coloring
	int Coloring(list<Node*> nodes_, bool imp=false ) {
		for (typename list<Node*>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {
			(*it)->colored = false;
			(*it)->color = 0;
		}
		int maxColores = 0;
		int i = 1;
		for (typename list<Node*>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {
			int col = i;
			vector<int> colores;
			auto et = (*it)->edges.begin();
			for (; et != (*it)->edges.end(); ++et) {
				if ((*et)->nodes[0] == (*it)) {
					if ((*et)->nodes[1]->colored == true) {
						colores.push_back((*et)->nodes[1]->color);
					}
				}
				else if ((*et)->nodes[1] == (*it)) {
					if ((*et)->nodes[0]->colored == true) {
						colores.push_back((*et)->nodes[0]->color);
					}
				}
			}
			col = menColor(colores);
			(*it)->colored = true;
			(*it)->color = col;
			if(imp == true ) cout << "Nodo " << (*it)->node_value << " -> Color " << (*it)->color << endl;
		}
		maxColores = cantColores(nodes_);
		if (imp == true) cout << "---------------------------------------------------------------------------------"<< endl;
		return maxColores;
	}
};


int main() {
	int n;
	Graph<char, int> g;
	cout << "------ Graph -------" << endl;
	cout << "  1 = Problema de Clase" << endl;
	cout << "  2 = Agregar Nodos" << endl;
	cout << "  3 = Agregar Edge" << endl;
	cout << "  4 = Eliminar nodo" << endl;
	cout << "  5 = Eliminar Edge" << endl;
	cout << "  6 = Imprimir Coloreo" << endl;
	cout << "  7 = Terminar" << endl;

	Graph<char, int> gr;
	bool code = true;
	char tecla;
	while (code) {
		cout << endl;
		cout << "- Chose an a option: ";
		cin >> tecla;
		cout << endl;

		switch (tecla) {
		case '1':
			gr.InsertNode('a');
			gr.InsertNode('b');
			gr.InsertNode('c');
			gr.InsertNode('d');
			gr.InsertNode('e');
			gr.InsertNode('f');
			gr.InsertEdge('a', 'b', 1, 0);
			gr.InsertEdge('a', 'd', 1, 0);
			gr.InsertEdge('a', 'f', 1, 0);
			gr.InsertEdge('f', 'b', 1, 0);
			gr.InsertEdge('f', 'e', 1, 0);
			gr.InsertEdge('e', 'c', 1, 0);
			gr.InsertEdge('e', 'd', 1, 0);
			gr.GraphColoring();
			code = false;
			break;

		case '2':
			cout << "Cuantos nodos desea?" << endl;
			cout << ">> ";
			cin >> n;
			for (int i = 0; i < n; i++) {
				char  valor;
				cout << "Nodo " << i + 1 << ",  Que letra desea que tenga el nodo = "
					;
				cin >> valor;
				g.InsertNode(valor);
			}
			break;

		case '3':
			char nodo1, nodo2;
			int peso;
			bool dir;
			cout << "Ingrese los dos nodos que quiere conectar:" << endl;
			cout << "Primero Nodo >> ";
			cin >> nodo1;
			cout << "Segundo Nodo >> ";
			cin >> nodo2;
			cout << "Peso >> ";
			cin >> peso;
			cout << "Direccion " << endl;
			cout << "0. <->" << endl;
			cout << "1. ->" << endl;
			cin >> dir;
			g.InsertEdge(nodo1, nodo2, peso, dir);
			break;


		case '4':
			char nodo3;
			cout << "Ingrese el nodo que quiere eliminar:" << endl;
			cin >> nodo3;
			g.RemoveNode(nodo3);
			break;

		case '5':
			char nodo4, nodo5;
			int peso1;
			cout << "Ingrese los dos nodos que quiere desconectar:" << endl;
			cout << "Primero Nodo >> ";
			cin >> nodo4;
			cout << "Segundo Nodo >> ";
			cin >> nodo5;
			cout << "Peso del edge a eliminar>> ";
			cin >> peso1;
			g.RemoveEdge(nodo4, nodo5, peso1);
			break;

		case '6':
			cout << "Coloreo: ";
			g.GraphColoring();
			break;

		case '7':
			code = false;
			break;
		}
	}


}
