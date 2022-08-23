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
#define DEBUG(x) cerr << #x << " = "; print(x)
const int mod = (int)1e9 + 7;

#ifdef __FILE_INPUT__

std::ifstream in;
std::ofstream out;

#define cin in
#define cout out

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

template<typename T> void print(const T& val, bool end_line = true, char sep = '\0') {
    cout << val << sep;
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


map<pair<int, int>, int> edge_cost;

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

vector<int> dijkstra(INT_MATRIX &g, int src) {

    const size_t n = g.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[src] = 0;

    auto cmp = [](pair<int, int> a, pair<int, int> b) {return a.second > b.second;};


    priority_queue <pair<int, int>, vector<pair<int, int>>, decltype(cmp)>  pq(cmp);
    pq.push(make_pair(src, 0));

    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();
        
        int index = v.first, min_value = v.second;
        visited[index] = true;

        if (dist[index] < min_value)
            continue;

        for (auto e : g[index]) {
            if (visited[e]) continue;
            int new_dist = dist[index] + edge_cost[make_pair(index, e)];
            if (new_dist < dist[e]) {
                dist[e] = new_dist;
                pq.push(make_pair(e, new_dist));
            }
        }
    }

    for (auto &el : dist)
        if (el == INT_MAX) el = -1;

    return dist;
}


int main () {

    auto g = get_graph();

    int start, end;
    cin >> start >> end;

    auto dist = dijkstra(g, start);
    cout << dist[end] << endl;

}


