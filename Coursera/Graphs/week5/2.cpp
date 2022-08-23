
#ifndef UNION_TABLE_H
#define UNION_TABLE_H


class union_table {

    int numComponents;

    int* sz;
    int* id;

public:

    union_table() {
        numComponents = 0;
    }

    union_table(int __n) {
        numComponents = __n;

        sz = new int[__n];
        id = new int[__n];

        for (int i = 0; i < __n; i++) {
            sz[i] = 1;
            id[i] = i;
        }

    }

    int find(int p) {

        // Find the root group for an element
        int root = p;
        while (root != id[root])
            root = id[root];


        // Appling path compression to a element
        while (p != id[p]) {
            int next = id[p];
            id[p] = root;
            p = next;
        }

        return root;
    }

    bool is_connected(int p, int q) {
        return find(p) == find(q);
    }

    int component_size() {
        return numComponents;
    }

    int size(int p) {
        return sz[find(p)];
    }

    // Joins element p and element q to same group
    void unify(int p, int q) {
        int root_p = find(p);
        int root_q = find(q);

        // p and q already in same group.
        if (root_p == root_q) return;

        // Adding smaller group to a larger group
        if (sz[root_p] < sz[root_q]) {
            sz[root_q] += sz[root_p];
            id[root_p] = root_q;
        } else {
            sz[root_p] += sz[root_q];
            id[root_q] = root_p;
        }

        numComponents--;
    }


};


#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


class edge {

public:

    int from, to;
    double cost;

    edge() {
        from = to = 0;
    }

    edge(int _from, int _to, double _cost) {
        from = _from;
        to   = _to;
        cost = _cost;
    }

};

void print(vector<edge> &list) {
    for (auto edge : list) {
        cout << "From : " << edge.from << " | To : " << edge.to;
        cout << " | Cost : " << edge.cost << endl;
    }
}

vector<edge> get_graph(int n) {
    vector<edge> list;
    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;

    auto cmp = [](pair<int, int> a, pair<int, int> b) {
        if (a.first < b.first) return true;
        if (a.first > b.first) return false;
        return a.second > b.second;
    };

    sort(points.begin(), points.end(), cmp);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist_x = points[i].first - points[j].first;
            int dist_y = points[i].second - points[j].second;

            double cost = sqrt(dist_x * dist_x + dist_y * dist_y);
            list.emplace_back(edge(i, j, cost));
        }
    }

    return list;
}

double cluster(int n, int K, vector<edge> &edge_list) {
    
    union_table u(n);
    double answer = edge_list.back().cost;

    for (auto e : edge_list) {
        if (!u.is_connected(e.from, e.to))
            u.unify(e.from, e.to);
        if (u.component_size() <= K)
            break;
    }

    for (auto e : edge_list)
        if (!u.is_connected(e.from, e.to))
            answer = min(answer, e.cost);

    return answer;
}

int main() {

    int n, K;
    cin >> n;

    auto edge_list = get_graph(n);
    cin >> K;

    auto cmp = [](edge a, edge b) { return a.cost < b.cost; };
    sort(edge_list.begin(), edge_list.end(), cmp);
    // print(edge_list);

    auto res = cluster(n, K, edge_list);
    cout << setprecision(10) << res << endl;
}

