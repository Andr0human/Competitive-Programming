
#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0);
#define INT_MATRIX vector<vector<int>>
#define DEBUG(x) cout << #x << " = "; print(x)
const int mod = (int)1e9 + 7;

#ifdef __FILE_INPUT__

std::ifstream in;
std::ofstream out;

#define cin in
#define cout out
#define endl '\n'

void open_files(string infile_name, string outfile_name) {

    in.open(infile_name);
    out.open(outfile_name);

}
void close_files() {

    in.close();
    out.close();

}

#endif

string input() {
    string text;
    getline(cin, text);
    return text;
}
int64_t ToInt(const string &__s) {
    int64_t value = 0;
    bool neg = (__s[0] == '-');
    const size_t f = neg ? 1 : 0;
    const size_t n = __s.length();

    for (size_t i = f; i < n; i++)
        value = 10 * value + (__s[i] - '0');

    value = neg ? -value : value;
    return value;
}
string ToStr(const bool _X) {
    return _X ? yes : no;
}

template<typename T> void read(vector<T> &arr) {
    for (T &element : arr) cin >> element;
}
template<typename T> void read(T arr[], size_t N) {
    for (size_t i = 0; i < N; i++) cin >> arr[i];
}
template<typename T> void read(vector<vector<T>> &arr) {
    for (vector<T> &vec : arr) for (T &element : vec) cin >> element;
}
template<typename T, typename U> void read(pair<T, U> &arr) {
    cin >> arr.first >> arr.second;
}

template<typename T> void print(const T& val, bool end_line = true) {
    cout << val;
    if (end_line) cout << endl;
}
template<typename T> void print(const vector<T> &arr, bool end_line = true, char sep = ' ') {
    const size_t __n = arr.size();
    if (!__n) return;
    for (size_t i = 0; i < __n - 1; i++) cout << arr[i] << sep;
    cout << arr[__n - 1];
    if (end_line) cout << endl;
}
template<typename T> void print(const T arr[], size_t __n, bool end_line = true, char sep = ' ') {
    if (!__n) return;
    for (size_t i = 0; i < __n - 1; i++) cout << arr[i] << sep;
    cout << arr[__n - 1];
    if (end_line) cout << endl;
}
template<typename T> void print(const vector<vector<T>> &arr, bool end_line = true) {
    cout << endl;
    const size_t __n = arr.size();
    if (!__n) return;
    for (size_t i = 0; i < __n - 1; i++) print(arr[i]);
    print(arr[__n - 1], end_line);
}
template<typename T, typename U> void print(const pair<T, U> &p, bool end_line = true) {
    cout << "(";
    print(p.first, false);
    cout << ", ";
    print(p.second, false);
    cout << ")";
    if (end_line) cout << endl;
}
template<typename T> void print(const set<T> &arr) {
    cout << endl;
    for (const T &val : arr) print(val);
}
template<typename T, typename U> void print(const map<T, U> &arr) {
    cout << endl;
    for (const auto i : arr) {
        print(i.first, false);
        cout << " -> ";
        print(i.second);
    }
}

template<typename T> vector<T> remove_duplicates(vector<T> arr) {
    if (!arr.size()) return std::vector<T>();
    sort(arr.begin(), arr.end());
    std::vector<T> res(1, arr[0]);
    for (T val : arr) if (res.back() != val) res.emplace_back(val);
    return res;
}
template<typename T> T min_of(const vector<T> &arr) {
    T best = arr[0];
    for (T val : arr) if (val < best) best = val;
    return best;
}
template<typename T> T max_of(const vector<T> &arr) {
    T best = arr[0];
    for (T val : arr) if (val > best) best = val;
    return best;
}
template<typename T> T sum_of(const vector<T> &arr) {
    T res = 0;
    for (T val : arr) res += val;
    return res;
}

#endif


const int64_t INF = 1e16;
map<pair<int, int>, int64_t> edge_cost;

INT_MATRIX get_graph() {
    int n, m;
    cin >> n >> m;

    INT_MATRIX g(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        g[x].emplace_back(y);
        edge_cost[make_pair(x, y)] = cost;
    }
    return g;
}

vector<int64_t> bellman_floyd(INT_MATRIX &g, int src) {

    const int V = g.size() - 1;

    vector<int64_t> dist(V + 1, INF);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int vt = 1; vt <= V; vt++) {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt]) {
                auto vt_edge = make_pair(vt, edge);
                int64_t newDist = dist[vt] + edge_cost[vt_edge];
                if (newDist < dist[edge])
                    dist[edge] = newDist;
            }
        }
    }

    for (int i = 0; i < V - 1; i++) {
        for (int vt = 1; vt <= V; vt++) {
            if (dist[vt] == INF) continue;
            for (auto edge : g[vt]) {
                auto vt_edge = make_pair(vt, edge);
                if (dist[vt] + edge_cost[vt_edge] < dist[edge])
                    dist[edge] = -INF;
            }
        }
    }

    return dist;
}


void print_answer(vector<int64_t> &dist) {
    const int n = dist.size();
    for (int i = 1; i < n; i++) {
        if (dist[i] == INF)
            cout << "*\n";
        else if (dist[i] == -INF)
            cout << "-\n";
        else
            cout << dist[i] << '\n';
    }
}

int main() {
    FAST_IO

    auto g = get_graph();
    int src;
    cin >> src;
    auto dist = bellman_floyd(g, src);

    print_answer(dist);

}


/* 10 13
7 8 -50
8 9 -10
2 7 60
6 7 5
6 9 50
1 2 5
2 6 30
2 3 20
6 5 25
3 4 10
4 3 -15
3 5 75
5 10 100
1 */

