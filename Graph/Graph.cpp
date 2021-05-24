#include <iostream> 
#include <string>
#include <list> 
#include <vector>
#include <algorithm>
using namespace std;

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
	int menColor(vector<int> &v) {
		sort(v.begin(), v.end());
		int t = 1;
		for (auto r = v.begin(); r != v.end(); ++r) {
			if (t != *r  ) return t;
			t++;
		}
		return t ;
	}
	// Coloring
	void Coloring() {
		int i = 1;
		for (typename list<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
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
			cout << "Nodo " << (*it)->node_value << " -> Color " << (*it)->color << endl;
		}
	}
};


int main() {
	int n;
	Graph<char, int> g;
	cout << "------ Graph -------" << endl;
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

	cout << endl;
	cout << "  1 = Agregar Edge" << endl;
	cout << "  2 = Eliminar nodo" << endl;
	cout << "  3 = Eliminar Edge" << endl;
	cout << "  4 = Imprimir Coloreo" << endl;
	cout << "  5 = Terminar" << endl;


	bool code = true;
	char tecla;
	while (code) {
		cout << endl;
		cout << "- Chose an a option: ";
		cin >> tecla;
		cout << endl;

		switch (tecla) {
		case '1':
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
			cout << "0. <->"<<endl;
			cout << "1. ->" << endl;
			cin >> dir;
			g.InsertEdge(nodo1, nodo2, peso, dir);
			break;
		case '2':
			char nodo3;
			cout << "Ingrese el nodo que quiere eliminar:" << endl;
			cin >> nodo3;
			g.RemoveNode(nodo3);
			break;
		case '3':
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
		case '4':
			cout << "Coloreo: ";
			g.Coloring();
			break;

		case '5':
			code = false;
			break;
		}
	}


}
