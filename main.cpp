#include "Graph.hpp"

#include <iostream>
#include <random>

int main() {
    Graph<int, int> graph;

    /*
    std::random_device dev;
    std::default_random_engine eng(dev());
    std::uniform_int_distribution<int> dist(0, nodes.size());

    const auto gen = [&dist, &eng] () {
        return dist(eng);
    };
    */

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

    std::cout << "graph:" << std::endl;
    graph.print(std::cout);

    std::cout << "msp: " << std::endl;
    tree.print(std::cout);
}
