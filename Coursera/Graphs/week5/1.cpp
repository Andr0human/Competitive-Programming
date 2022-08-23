#include <bits/stdc++.h>
using namespace std;

int square(int x) {
    return x * x;
}

class edge {

    public:

    int from;
    int to;
    int cost;

    edge() {
        from = to = cost = 0;
    }

    edge(int f, int t, int c) {
        from = f;
        to = t;
        cost = c;
    }

};

class union_table {

    size_t __size;
    size_t num_components;

    vector<int> sz;
    vector<int> id;

    public:

    union_table(size_t __n) {
        __size = num_components = __n;
        sz.resize(__n);
        fill(sz.begin(), sz.end(), 1);

        id.resize(__n);
        for (size_t i = 0; i < __n; i++)
            id[i] = i;
    }

    int find(int p) {
        int root = p;
        while (root != id[root])
            root = id[root];

        while (p != root) {
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
        return num_components;
    }

    int size(int p) {
        return sz[find(p)];
    }

    void unify(int p, int q) {
        int root1 = find(p);
        int root2 = find(q);

        // Both are already in same group
        if (root1 == root2) return;

        // Merge smaller into larger group

        if (sz[root1] < sz[root2]) {
            sz[root2] += sz[root1];
            id[root1]  = root2;
        } else {
            sz[root1] += sz[root2];
            id[root2]  = root1;
        }

        // Reduce no. of components by one.
        num_components--;
    }

    void print() {
        for (auto i : id)
            cout << i << " ";
        cout << endl;
    }

};

void print(vector<edge> & list) {
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

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto p = points[i], q = points[j];
            int cost = square(abs(p.first - q.first)) + square(abs(p.second - q.second));
            list.emplace_back(edge(i, j, cost));
        }
    }

    return list;
}

vector<edge> kruskal(int n, vector<edge> &edge_list) {

    union_table u(n);
    vector<edge> res;

    for (auto e : edge_list) {
        if (u.is_connected(e.from, e.to))
            continue;
        u.unify(e.from, e.to);
        res.emplace_back(e);
    }
    return res;
}

double final_cost(vector<edge> list) {
    double res = 0;
    for (auto e : list)
        res += sqrt(e.cost);
    return res;
}

int main() {
    
    int n; cin >> n;
    auto edge_list = get_graph(n);
    auto cmp = [](edge a, edge b) {
        return a.cost < b.cost;
    };


    sort(edge_list.begin(), edge_list.end(), cmp);
    // print(edge_list);

    auto res = kruskal(n, edge_list);
    // cout << "Printing res = \n";
    // print(res);
    cout << setprecision(10) << final_cost(res) << endl;

}


/*

0 0 - 0
0 2 - 1
1 1 - 2
3 0 - 3
3 2 - 4


*/
