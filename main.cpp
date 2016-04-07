#include "Graph.hpp"

#include <iostream>
#include <random>

int main() {
    Graph<int, int> graph;

    std::vector<int> nodes;

    for (int i = 0; i < 10000; i++) {
        nodes.push_back(i);
        graph.add_node(nodes[i]);
    }

    std::random_device dev;
    std::default_random_engine eng(dev());
    std::uniform_int_distribution<int> dist(0, nodes.size());

    const auto gen = [&dist, &eng] () {
        return dist(eng);
    };

    for (int i = 0; i < 2000000; i++) {
        int a = gen();
        int b = gen();

        while (a == b) {
            b = gen();
        }

        graph.add_edge(nodes[a], nodes[b], gen());
    }
    
    //graph.print(std::cout);
}
