#include <bits/stdc++.h>
using namespace std;


#ifndef TEMPLATES

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
#define FAST_IO std::ios::sync_with_stdio(0); std::cin.tie(0);
#define INT_MATRIX std::vector<std::vector<int>>
#define DEBUG(x) cerr << #x << " = " << x << endl
const int mod = (int)1e9 + 7;

#ifdef __FILE_INPUT__

std::ifstream in;
std::ofstream out;

#define cin in
#define cout out

#endif

int next() {
    ll tmp; cin >> tmp;
    return tmp;
}
std::string nextstr() {
    std::string tmp; cin >> tmp;
    return tmp;
}
std::string ToStr(const bool _X) {
    return _X ? yes : no;
}
template<typename T> void read(vector<T> &arr) {
    for (T &element : arr) cin >> element;
} 
template<typename T> void print(const vector<T> &arr, char end = ' ') {
    for (T element : arr) cout << element << end;
    cout << std::endl;
}
template<typename T> void read(T arr[], size_t N) {
    for (size_t i = 0; i < N; i++) cin >> arr[i];
}
template<typename T> void print(const T arr[], size_t N, char end = ' ') {
    for (size_t i = 0; i < N; i++) cout << arr[i] << end;
    cout << std::endl;
}
template<typename T> void read(vector<vector<T>> &arr) {
    for (vector<T> &vec : arr) for (T &element : vec) cin >> element;
}
template<typename T> void print(const vector<vector<T>> &arr) {
    for (vector<T> vec : arr) {
        for (T element : vec) cout << element << " ";
        cout << std::endl;
    }
}
template<typename T, typename U> void print(map<T, U> &arr) {
    for (auto i : arr)
        cout << i.first << " -> " << i.second << '\n';
    cout << std::endl;
}
template<typename T> std::vector<T> remove_duplicates(vector<T> arr) {
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
template<typename T, typename U> void read(std::pair<T, U> &arr) {
    cin >> arr.first >> arr.second;
}
template<typename T, typename U> void print(const std::pair<T, U> &arr) {
    cout << "(" << arr.first << ", " << arr.second << ")" << std::endl;
}
template<typename T> T sum_of(const vector<T> &arr) {
    T res = 0;
    for (T val : arr) res += val;
    return res;
}

#endif



vector<bool> visited;
vector<int> post_order;

INT_MATRIX rev(const INT_MATRIX &arr) {
    INT_MATRIX res(arr.size(), vector<int>());
    
    for (size_t i = 1; i < arr.size(); i++)
        for (int j : arr[i])
            res[j].emplace_back(i);
    return res;
}

INT_MATRIX get_graph() {
    int n, m;
    cin >> n >> m;

    INT_MATRIX g(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
    }
    return g;
}

void dfs(const INT_MATRIX &g, int vertex, int &order) {
    visited[vertex] = true;
    for (int edge : g[vertex])
        if (!visited[edge])
            dfs(g, edge, order);
    post_order[order++] = vertex;
}

void explore(const INT_MATRIX &g, int vertex) {
    visited[vertex] = true;
    for (int edge : g[vertex])
        if (!visited[edge])
            explore(g, edge);
}

void scc(const INT_MATRIX &g, const INT_MATRIX &rg) {

    const int n = g.size();
    post_order.resize(n);
    visited.resize(n);

    int order = 1;
    for (int i = 1; i < n; i++)
        if (!visited[i])
            dfs(rg, i, order);

    // print(post_order);

    for (int i = 1; i < n; i++)
        visited[i] = false;
    
    int answer = 0;
    for (int i = n - 1; i >= 1; i--) {
        int vertex = post_order[i];
        if (!visited[vertex]) {
            explore(g, vertex);
            answer++;
        }
    }
    
    cout << answer << endl;
}

int main() {
    
    INT_MATRIX g = get_graph();
    INT_MATRIX rev_g = rev(g);

    scc(g, rev_g);

}

