#ifndef DIAMETER_HPP
#define DIAMETER_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

typedef int node;
typedef unordered_map<node, unordered_set<node>> graph;

void add_node(graph &g, const node &n) {
    g.emplace(n, unordered_set<node>());
}

void add_arch(graph &g, const node &a, const node &b) {
    g.find(a)->second.insert(b);
}

unordered_set<node> adj(const graph &g, const node &n) {
    auto it = g.find(n);
    return it == end(g) ? unordered_set<node>() : it->second;
}

template<typename K, typename V>
V take_second(const pair<K, V> &p) {
    return p.second;
}

template<typename K, typename V>
K take_first(const pair<K, V> &p) {
    return p.first;
}

template<typename K, typename V>
bool max_second(const pair<K, V> &a, const pair<K, V> &b) {
    return a.second < b.second;
}

template<typename K, typename V>
bool contains(const unordered_map<K, V> &map, const K &key) {
    return map.find(key) != end(map);
}

function<int(const node)> max_erdos(const graph &g) {
    return [&](const node &n) {
        unordered_map<node, int> erdos = {{n, 0}};
        queue<node> q;
        q.push(n);

        while (!q.empty()) {
            auto u = q.front();
            auto e = erdos.find(u)->second;
            q.pop();
            for (node a : adj(g, u)) {
                if (!contains(erdos, a)) {
                    erdos.insert({a, e + 1});
                    q.push(a);
                }
            }
        }

        return max_element(begin(erdos), end(erdos), max_second<node, int>)->second;
    };
}

template<typename T, typename K, typename V>
function<T(const pair<K, V>)> firsts(const function<T(const K)> &op) {
    return [&](const pair<K, V> &p) {
        return op(p.first);
    };
}

int max_diameter(const graph &g) {
    unordered_set<int> ds;
    transform(begin(g), end(g), inserter(ds, begin(ds)), firsts<int, node, unordered_set<node>>(max_erdos(g)));
    return *max_element(begin(ds), end(ds));
}

graph from_stream(std::istream &input, const int nodes, const int arches) {
    graph g;

    for (node n = 0; n < nodes; n++) {
        add_node(g, n);
    }

    for (auto i = 0; i < arches; i++) {
        node a;
        node b;

        input >> a >> b;
        add_arch(g, a, b);
        add_arch(g, b, a);
    }
    return g;
}

int diameter(std::istream &input) {
    int n;
    int m;

    input >> n >> m;
    return max_diameter(from_stream(input, n, m));
}

#endif //DIAMETER_HPP
