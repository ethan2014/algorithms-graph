#include "Graph.hpp"

#include <iostream>
#include <random>

template <typename T>
void print_msp(const T& graph) {
    const auto msp = graph.minimum_spanning_tree();
    msp.print(std::cout);
}

template <typename Graph>
void print_shortest_path(const Graph& graph) {
    int from;
    int to;

    std::cout << "enter a node: ";
    std::cin >> from;

    std::cout << "enter another node: ";
    std::cin >> to;
    
    const auto path = graph.shortest_path(from, to);

    for (const auto& i : path) {
	std::cout << i << " -> ";
    }

    std::cout << "DONE" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
	std::cout << "usage: graph [file]" << std::endl;
	return 0;
    }
    
    Graph<int, int> graph;

    graph.load(argv[1]);

    auto input = '0';

    while (input != '6') {
	std::cout << "choose an option:" << std::endl;
	std::cout << "0: print the graph" << std::endl;
	std::cout << "1: add a node" << std::endl;
	std::cout << "2: add an edge" << std::endl;
	std::cout << "3: check if edge exists" << std::endl;
	std::cout << "4: print the msp" << std::endl;
	std::cout << "5: find shortest path" << std::endl;
	std::cout << "6: exit" << std::endl;

	std::cin >> input;

	int node1;
	int node2;

	switch (input) {
	case '0':
	    graph.print(std::cout);
	    break;
	case '1':
	    int node;
	    std::cout << "enter a node value: ";
	    std::cin >> node;
	    std::cout << std::endl;
	    graph.add_node(node);
	    break;
	case '2':
	    int weight;
	    std::cout << "enter node 1: ";
	    std::cin >> node1;
	    std::cout << "enter node 2: ";
	    std::cin >> node2;
	    std::cout << "enter weight: ";
	    std::cin >> weight;
	    graph.add_edge(node1, node2, weight);
	    break;
	case '3':
	    std::cout << "enter node 1: ";
	    std::cin >> node1;
	    std::cout << "enter node 2: ";
	    std::cin >> node2;
	    std::cout << std::endl;
	    std::cout << "edge from " << node1
		      << " to " << node2 << "? "
		      << std::boolalpha << graph.edge_exists(node1, node2) << std::endl;
	    break;
	case '4':
	    std::cout << std::endl;
	    print_msp(graph);
	    break;
	case '5':
	    std::cout << std::endl;
	    print_shortest_path(graph);
	    break;
	case '6':
	    break;
	default:
	    std::cout << "unknown command" << std::endl;
	}

	std::cout << std::endl;
    }
    

    /*
    std::random_device dev;
    std::default_random_engine eng(dev());
    std::uniform_int_distribution<int> dist(0, nodes.size());

    const auto gen = [&dist, &eng] () {
        return dist(eng);
    };
    */
    /*
    graph.add_node(1);
    graph.add_node(2);
    graph.add_node(3);
    graph.add_node(4);
    graph.add_node(5);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);
    
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 2, 2);
    
    graph.add_edge(3, 4, 2);
    graph.add_edge(4, 3, 2);

    graph.add_edge(4, 5, 3);
    graph.add_edge(5, 4, 3);

    graph.add_edge(1, 5, 2);
    graph.add_edge(5, 1, 2);

    graph.add_edge(2, 5, 1);
    graph.add_edge(5, 2, 1);

    graph.add_edge(2, 4, 1);
    graph.add_edge(4, 2, 1);

    const auto tree = graph.minimum_spanning_tree();

    const auto path = graph.shortest_path(1, 1);

    std::cout << "graph:" << std::endl;
    graph.print(std::cout);

    std::cout << "msp: " << std::endl;
    tree.print(std::cout);

    std::cout << "path from 1 to 1:" << std::endl;
    for (const auto& i : path) {
	std::cout << i << " -> ";
    }
    std::cout << std::endl;

    graph.load("graph.txt");

    graph.print(std::cout);
    */
}
