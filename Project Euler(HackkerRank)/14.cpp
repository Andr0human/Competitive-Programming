/***
 *  Project Euler #14: Longest Collatz sequence
 *  Collatz Conjucture : Any no. n that follows [ n -> if n is even then n / 2, else 3 * n + 1] will eventually reach 1.
 *  Approach : Calculate the no. of steps for every no. (Use memoization otherwise TLE)
 *             Create a prefixBest array to process each query in O(1). (may give TLE if used an O(n) approach)
***/


#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxN = (ll)5e6 + 5;

int collatz(ll n, vector<int> &arr) {
    int res = 0, num = n;
    while (n != 1) {
        n = n & 1 ? 3 * n + 1 : n >> 1;     // Collatz Rule for next number
        res++;                              // Add to total steps
        if (n < num) return res + arr[n];   // Memoise (Add result from previously calculated values)
    }
    return res;
}

vector<int> collatzList() {
    vector<int> arr(maxN + 1);
    for (int i = 1; i <= maxN; i++)
        arr[i] = collatz(i, arr);
    return arr;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    vector<int> list = collatzList();
    vector<int> answer(maxN + 1);

    // Convert the list to a prefixMax list to each query in O(1)
    for (size_t i = 1; i <= maxN; i++)
        answer[i] = list[answer[i - 1]] > list[i] ? answer[i - 1] : i;

    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        ll ans = answer[N];
        cout << ans << endl;
    }
    
}
