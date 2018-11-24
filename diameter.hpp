#ifndef DIAMETER_HPP
#define DIAMETER_HPP

#include <algorithm>
#include <fstream>
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

template<typename K, typename V>
K take_first(const pair<K, V> &p) {
    return p.first;
}

template<class OutputIterator>
void nodes(const graph &g, OutputIterator out) {
    transform(begin(g), end(g), out, take_first<node, unordered_set<node>>);
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
            for (node a : g.find(u)->second) {
                if (!contains(erdos, a)) {
                    erdos.insert({a, e + 1});
                    q.push(a);
                }
            }
        }

        return max_element(begin(erdos), end(erdos), max_second<node, int>)->second;
    };
}

int max_diameter(const graph &g) {
    unordered_set<int> ns;
    nodes(g, inserter(ns, begin(ns)));
    unordered_set<int> ds;
    transform(begin(ns), end(ns), inserter(ds, begin(ds)), max_erdos(g));
    return *max_element(begin(ds), end(ds));
}

void from_stream(graph &g, istream &input, const int nodes, const int arches) {
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
}

int diameter(istream &input) {
    int n;
    int m;

    input >> n >> m;
    graph g;
    from_stream(g, input, n, m);
    return max_diameter(g);
}

#endif //DIAMETER_HPP
