#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <exception>
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <stack>
#include <tuple>

template <typename T, typename E>
class Node {
public:
    T value;

    std::unordered_map<T, E> neighbors;

    Node() {
	
    }

    Node(T val) : value{ std::move(val) } {

    }

    auto operator==(const Node<T, E>& other) const {
	return value == other.value;
    }
};

template <typename T, typename E>
class Graph {
private:
    std::unordered_map<T, Node<T, E>> nodes;

    auto dijkstra_min_edge(const std::vector<Node<T, E>>& s,
			   const std::unordered_map<T, E>& weights) const;

public:
    void print(std::ostream& out) const;

    void load(const std::string& filename);
    
    void add_node(T val);
    void del_node(const T& val);

    void add_edge(const T& from, const T& to, E weight);
    void del_edge(const T& from, const T& to);

    bool edge_exists(const T& from, const T& to) const;

    auto get_edge(const T& from, const T& to) const;

    const auto node_count() const;
    const auto edge_count() const;

    const auto& neighbors(const T& from) const;

    auto shortest_path(const T& from, const T& to) const;
    auto minimum_spanning_tree() const;
    auto minimum_connection(const std::vector<Node<T, E>>& x,
			    const std::vector<Node<T, E>>& y) const;
};

template <typename T, typename E>
auto Graph<T, E>::dijkstra_min_edge(const std::vector<Node<T, E>>& s,
				    const std::unordered_map<T, E>& weights) const {
    const T* min_node1 = nullptr;
    const T* min_node2 = nullptr;
    const E* min_weight = nullptr;
    
    for (const auto& s_node : s) {
	for (const auto& neighbor : s_node.neighbors) {
	    const auto found = std::any_of(std::begin(s), std::end(s),
					   [&neighbor] (const auto& n) {
					       return neighbor.first == n.value;
					   });

	    if (!found) {
		const auto weight = weights.at(s_node.value) + neighbor.second;
		
		if (min_node1 == nullptr || weight < *min_weight) {
		    min_node1 = &s_node.value;
		    min_node2 = &neighbor.first;
		    min_weight = &neighbor.second;
		} 
	    }
	}
    }

    return std::make_tuple(*min_node1, *min_node2, *min_weight);
}

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
void Graph<T, E>::load(const std::string& filename) {
    nodes.clear();
    
    std::ifstream file{ filename };

    std::string in;

    auto read_nodes = true;

    while (file >> in) {
	if (in == "nodes:") {
	    read_nodes = true;
	} else if (in == "edges:") {
	    read_nodes = false;
	} else if (read_nodes) {
	    add_node(std::stoi(in));
	} else {
	    auto u = std::stoi(in);
	    file >> in;
	    auto v = std::stoi(in);
	    file >> in;
	    auto e = std::stoi(in);

	    add_edge(u, v, e);
	}
    }
}

template <typename T, typename E>
void Graph<T, E>::add_node(T val) {
    nodes[val] = Node<T, E>{ val };
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

    it->second.neighbors[to] = weight;
}

template <typename T, typename E>
void Graph<T, E>::del_edge(const T& from, const T& to) {
    auto outer_it = nodes.find(from);

    if (outer_it == std::end(nodes)) {
        return;
    }

    auto it = outer_it->second.neighbors.find(to);

    if (it == std::end(outer_it->second.neighbors)) {
	return;
    }

    outer_it->second.neighbors.erase(it);
}

template <typename T, typename E>
bool Graph<T, E>::edge_exists(const T& from, const T& to) const {
    auto outer_it = nodes.find(from);

    if (outer_it == std::end(nodes)) {
        return false;
    }

    for (const auto& node : outer_it->second.neighbors) {
	if (to == node.first) {
	    return true;
	}
    }

    return false;
}

template <typename T, typename E>
auto Graph<T, E>::get_edge(const T& from, const T& to) const {
    auto it = nodes.find(from);

    for (const auto& node : it->second.neighbors) {
	if (to == node.first) {
	    return node.second;
	}
    }

    throw std::runtime_error("edge does not exist");
}

template <typename T, typename E>
const auto Graph<T, E>::node_count() const {
    return nodes.size();
}

template <typename T, typename E>
const auto Graph<T, E>::edge_count() const {
    return std::accumulate(std::begin(nodes), std::end(nodes), 0,
			   [] (const auto total, const auto& node) {
			       return total + node.second.neighbors.size();
			   });
}

template <typename T, typename E>
const auto& Graph<T, E>::neighbors(const T& val) const {
    return nodes.find[val]->second.neighbors;
}

template <typename T, typename E>
auto Graph<T, E>::shortest_path(const T& from, const T& to) const {
    if (from == to) {
	return std::vector<T>{};
    }
    
    const auto from_node = nodes.at(from);
    const auto to_node = nodes.at(to);

    auto weights = std::unordered_map<T, E>{};
    auto paths = std::unordered_map<T, T>{};
    auto s = std::vector<Node<T, E>>{};

    weights[from] = E{};
    paths[from] = from;
    s.push_back(from_node);

    while (s.size() != nodes.size()) {
	auto u = T{};
	auto v = T{};
	auto e = E{};

	std::tie(u, v, e) = dijkstra_min_edge(s, weights);

	weights[v] = weights[u] + e;
	paths[v] = u;
	s.push_back(nodes.at(v));
    }

    auto ret = std::vector<T>{};

    auto node = to;

    while (node != from) {
	ret.insert(std::begin(ret), node);
	node = paths.at(node);
    }

    ret.insert(std::begin(ret), node);

    return ret;
}

template <typename T, typename E>
auto Graph<T, E>::minimum_spanning_tree() const {
    auto tree = Graph<T, E>{};

    auto x = std::vector<Node<T, E>>{};
    auto y = std::vector<Node<T, E>>{};

    x.push_back(nodes.begin()->second);

    for (auto it = std::next(std::begin(nodes), 1); it != std::end(nodes); ++it) {
	y.push_back(it->second);
    }

    for (const auto& node : nodes) {
	tree.add_node(node.first);
    }

    while (x.size() != nodes.size()) {
	auto u = T{};
	auto v = T{};
	auto e = E{};

	std::tie(u, v, e) = minimum_connection(x, y);

	std::cout << "adding " << u << " -> " << v << ", e = " << e << std::endl;

	auto node = nodes.find(v);

	x.push_back(node->second);
	y.erase(std::find(std::begin(y), std::end(y), node->second));

	for (const auto& i : y) {
	    std::cout << i.value << ", ";
	}

	std::cout << std::endl;

	tree.add_edge(u, v, e);
    }

    return tree;
}

template <typename T, typename E>
auto Graph<T, E>::minimum_connection(const std::vector<Node<T, E>>& x,
				     const std::vector<Node<T, E>>& y) const {
    const T* min_node1 = nullptr;
    const T* min_node2 = nullptr;

    auto min_edge = E{};

    for (const auto& outer_node : x) {
	for (const auto& inner_node : y) {
	    const auto exists = edge_exists(outer_node.value, inner_node.value);

	    if (!exists) {
		continue;
	    }
	    
	    const auto edge = get_edge(outer_node.value, inner_node.value);

	    if (min_node1 == nullptr || edge < min_edge) {
		min_node1 = &outer_node.value;
		min_node2 = &inner_node.value;
		min_edge = edge;
	    }
	}
    }

    return std::make_tuple(*min_node1, *min_node2, min_edge);
}


#endif
