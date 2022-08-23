#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
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
template<typename T> void print(const vector<T> &arr, char end = ' ') {
    for (T element : arr) std::cout << element << end;
    std::cout << std::endl;
}
template<typename T> void read(T arr[], size_t N) {
    for (size_t i = 0; i < N; i++) std::cin >> arr[i];
}
template<typename T> void print(const T arr[], size_t N, char end = ' ') {
    for (size_t i = 0; i < N; i++) std::cout << arr[i] << end;
    std::cout << std::endl;
}
template<typename T> void read(vector<vector<T>> &arr) {
    for (vector<T> &vec : arr) for (T &element : vec) std::cin >> element;
}
template<typename T> void print(const vector<vector<T>> &arr) {
    for (vector<T> vec : arr) {
        for (T element : vec) std::cout << element << " ";
        std::cout << std::endl;
    }
}
template<typename T, typename U> void print(map<T, U> &arr) {
    for (auto i : arr)
        std::cout << i.first << " -> " << i.second << '\n';
    std::cout << std::endl;
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

vector<bool> visited;

void explore_and_mark(int current, int value, vector<vector<int>> &arr) {

    for (int i : arr[current]) {
        if (visited[i]) continue;
        visited[i] = true;
        explore_and_mark(i, value, arr);
    }

}


int main() {
   
    int n, m, x, y;
    cin >> n >> m;

    visited.resize(n + 1, false);
    vector<vector<int>> points(n + 1, vector<int>());

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        points[x].emplace_back(y);
        points[y].emplace_back(x);
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        answer++;
        explore_and_mark(i, answer, points);
    }
    
    cout << answer;
}


