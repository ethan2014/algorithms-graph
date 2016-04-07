#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

template <typename T, typename E>
class Node {
public:
    T value;

    std::unordered_map<T, E> neighbors;

    Node() {
	
    }

    Node(T val) : value{ std::move(val) } {

    }
};

template <typename T, typename E>
class Graph {
private:
    std::unordered_map< T, Node<T, E> > nodes;

public:
    void print(std::ostream& out) const;
    
    void add_node(T val);
    void del_node(const T& val);

    void add_edge(const T& from, const T& to, E weight);
    void del_edge(const T& from, const T& to);

    bool edge_exists(const T& from, const T& to) const;

    const auto& neighbors(const T& from) const;
};

template <typename T, typename E>
void Graph<T, E>::print(std::ostream& out) const {
    out << "nodes: " << nodes.size() << std::endl;
    for (const auto& node : nodes) {
        std::cout << "node: val = " << node.first << ", neighbors = " << std::endl;
        for (const auto& n : node.second.neighbors) {
            std::cout << "    (E = " << n.second << ", V = " << n.first << ")" << std::endl;
        }
    }
}

template <typename T, typename E>
void Graph<T, E>::add_node(T val) {
    nodes[val] = std::move(Node<T, E>{ val });
}

template <typename T, typename E>
void Graph<T, E>::del_node(const T& val) {
    auto it = nodes.find(val);

    if (it == std::end(nodes)) {
        return;
    }

    nodes.erase(it);

    for (auto& node : nodes) {
	auto i = node.second.neighbors.find(val);

	if (i != std::end(node.second.neighbors)) {
	    node.second.neighbors.erase(i);
	}
    }
}

template <typename T, typename E>
void Graph<T, E>::add_edge(const T& from, const T& to, E weight) {
    auto it = nodes.find(from);

    if (it == std::end(nodes)) {
        return;
    }

    it->second.neighbors[to] = std::move(weight);
}
/*
template <typename T, typename E>
void Graph<T, E>::del_edge(const Node<T>& from, const Node<T>& to) {
    auto outer_it = std::find_if(std::begin(nodes), std::end(nodes),
                                 [&from] (const auto& outer_node) {
                                     return outer_node.node == from;
                                 });

    if (outer_it == std::end(nodes)) {
        return;
    }

    auto inner_it = std::find_if(std::begin(outer_it->neighbors), std::end(outer_it->neighbors),
                                 [&to] (const auto& node_pair) {
                                     return node_pair.second == to;
                                 });

    if (inner_it == std::end(outer_it->neighbors)) {
        return;
    }

    outer_it->neighbors.erase(inner_it);
}
*/

template <typename T, typename E>
bool Graph<T, E>::edge_exists(const T& from, const T& to) const {
    auto outer_it = nodes.find(from);

    if (outer_it == std::end(nodes)) {
        return false;
    }

    for (const auto& node : nodes) {
	auto it = node.second.neighbors.find(to);

	if (it != std::end(node.second.neighbors)) {
	    return true;
	}
    }

    return false;
}

template <typename T, typename E>
const auto& Graph<T, E>::neighbors(const T& val) const {
    return nodes[val]->neighbors;
}

#endif
