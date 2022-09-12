/***
 * Project Euler #30: Digit Nth powers
 * Approach : Find Upper Limit for using brute force.
 * Then just brute force will solve in required time.
***/

#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

template <typename T, typename U> T binpow(T base, U expo) {
    T res = 1;
    while (expo) {
        if (expo & 1) res *= base;
        expo >>= 1;
        base *= base;
    }
    return res;
}

template<typename T> std::vector<int> extract_digits(T _X) {
    std::vector<int> res;
    while (_X) {
        res.emplace_back(_X % 10);
        _X /= 10;
    }
    return res;
}

int sum_of_power(int number, int power) {
    vector<int> digits = extract_digits(number);
    int digits_sum = 0;
    for (int i = 0; i < digits.size(); i++)
        digits_sum += binpow(digits[i], power);
    return digits_sum;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int power, answer = 0;
    cin >> power;
    for (int i = 10; i <= 600000; i++)
        if (sum_of_power(i, power) == i) answer += i;
    std::cout << answer;
}

