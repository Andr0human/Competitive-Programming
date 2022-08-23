#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
#define DEBUG(x) std::cout << #x << " = " << x << std::endl;
#define FAST_IO std::ios::sync_with_stdio(0); std::cin.tie(0);
#define INT_MATRIX std::vector<std::vector<int>>

const int mod = (int)1e9 + 7;

#ifndef TEMPLATES

int next() {
    int tmp; std::cin >> tmp;
    return tmp;
}
ll nextll() {
    ll tmp; std::cin >> tmp;
    return tmp;
}
std::string nextstr() {
    std::string tmp; std::cin >> tmp;
    return tmp;
}
std::string ToStr(const bool _X) {
    return _X ? yes : no;
}
template<typename T> void read(vector<T> &arr) {
    for (T &element : arr) std::cin >> element;
} 
template<typename T> void print(const vector<T> &arr) {
    for (T element : arr) std::cout << element << " ";
    std::cout << std::endl;
}
template<typename T> void read(T arr[], int N) {
    for (size_t i = 0; i < N; i++) std::cin >> arr[i];
}
template<typename T> void print(const T arr[], int N) {
    for (size_t i = 0; i < N; i++) std::cout << arr[i] << " ";
    std::cout << std::endl;
}
template<typename T> void read(vector<vector<T>> &arr) {
    for (vector<T> &vec : arr) for (T &element : vec) std::cin >> element;
}
template<typename T> void print(vector<vector<T>> &arr) {
    for (vector<T> &vec : arr) {
        for (T element : vec) std::cout << element << " ";
        std::cout << std::endl;
    }
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
    std::cin >> arr.first >> arr.second;
}
template<typename T, typename U> void print(const std::pair<T, U> &arr) {
    std::cout << "(" << arr.first << ", " << arr.second << ")" << std::endl;
}
template<typename T> T sum_of(const vector<T> &arr) {
    T res = 0;
    for (T val : arr) res += val;
    return res;
}


#endif



vector<int> answer;
vector<bool> visited;

void explore(INT_MATRIX &arr, int vertex) {
    
    if (visited[vertex]) return;

    for (int edge : arr[vertex]) {
        if (!visited[edge])
            explore(arr, edge);
    }
    
    answer.emplace_back(vertex);
    visited[vertex] = true;
}

void topo_sort(INT_MATRIX &arr) {
    for (size_t i = 1; i < arr.size(); i++)
        explore(arr, i);
}

int main() {
    int n, m;
    cin >> n >> m;

    visited.resize(n + 1, false);
    INT_MATRIX vertices(n + 1, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        vertices[x].emplace_back(y);
    }

    topo_sort(vertices);
    reverse(answer.begin(), answer.end());
    print(answer);

}
