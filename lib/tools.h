/**
 * @file tools.h
 * @author Ayush Sinha
 * @brief Tools library contains common functions used in
 *        coding competitions.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_set>

using std::vector;
using std::string;

/**
 * @note
 * 
 */


namespace tools {

// Checks if a sequence is pallindromic
template<typename _RandomAccessIterator> constexpr bool
is_pallindrome(_RandomAccessIterator __first, _RandomAccessIterator __last) {

    size_t _Nm = (__last - __first) >> 1;

    while (_Nm-- > 0) {
        --__last;
        if (*__first != *__last) return false;
        ++__first;
    }

    return true;
}


// Returns no. of digits in number _X.
constexpr int len(int64_t _X) {
    const int64_t lt = 1e14, m = 1e9, rt = 1e5;
    int _r = 0;

    _X = __builtin_llabs(_X);
    _r  = _X >= m ? _X >= lt ? 14 : 9 : _X >= rt ?  5 : 0;
    _X /= _X >= m ? _X >= lt ? lt : m : _X >= rt ? rt : 1;
    _r += _X > 999 ? _X > 9999 ? 5 : 4 : _X > 9 ? _X > 99 ? 3 : 2 : 1;
    
    return _r;
}


// Returns A to the power B.
template <typename T, typename U>
constexpr inline T pow(T base, U expo) {
    T res = 1;
    while (expo) {
        res *= base * (expo & 1);
        expo >>= 1;
        base *= base;
    }
    return res;
}

// Returns A to the power B mod M.
template <typename T, typename U, typename V>
constexpr inline T pow(T base, U expo, V mod) {
    T res = 1;
    while (expo) {
        if (expo & 1) res = (res * base) % mod;
        expo >>= 1;
        base = (base * base) % mod;
    }
    return res;
}

// Returns the binary format for positive values for base 2 to 9.
const inline string bin(size_t num, size_t base = 2) {
    if (num == 0) return "0";
    
    string in_binary;
    while(num > 0) {
        in_binary.push_back(static_cast<char>(num % base) + '0');
        num /= base;
    }
    std::reverse(begin(in_binary), end(in_binary));
    return in_binary;
}

// Returns the least significant bit of an unsigned integer.
inline size_t lSb(size_t N) {
    return N ^ (N & (N - 1));
}

// Returns the most significant bit of an unsigned integer.
inline size_t mSb(size_t __x) {
    if (__x == 0) return 0;
    return (1ULL << (63 - __builtin_clzll(__x)));
}

// Returns the number of set bits in an integer.
inline int popCount(int32_t __x) {
    return __builtin_popcount(__x);
}

// Returns the number of set bits in a long integer.
inline int popCount(int64_t __x) {
    return __builtin_popcountll(__x);
}

/**
 * @brief Extract and returns all elements from a single string.
 * 
 * @param __s String
 * @param sep separator
 * @return const vector<string> 
 */
inline vector<string> split(const std::string &__s, const char sep) {
    vector<string> res;
    size_t prev = 0, __n = __s.length();

    for (size_t i = 0; i < __n; i++) {
        if (__s[i] != sep) continue;

        if (i > prev)
            res.emplace_back(__s.substr(prev, i - prev));
        prev = i + 1;
    }

    if (__n > prev)
        res.emplace_back(__s.substr(prev, __n - prev));

    return res;
}

/**
 * @brief Returns the stripped string from both ends
 * 
 * @param __s String
 * @param strip_list List of chars to be stripped from both ends
 * @return const string 
 */
inline string strip(const string &__s, const vector<char> &strip_list = vector<char>{' '}) {
    
    if (__s.empty()) return __s;

    // Checks if a string element belongs to strip_list
    const auto in_strip_list = [&strip_list] (char ch) {
        return std::any_of(begin(strip_list), end(strip_list),
            [ch] (char val) {
                return val == ch;
            }
        );
    };

    const auto f = std::find_if_not(begin(__s), end(__s), in_strip_list);
    const auto e = (std::find_if_not(rbegin(__s), rend(__s), in_strip_list)).base();

    // Stripped everything.
    if (f == end(__s)) return "";                       

    // Nothing to strip.
    if (f == begin(__s) && e == end(__s)) return __s;
    
    // Copying the remaining string after excluding stripped indexes
    std::string res;
    for (auto it = f; it != e; it++)
        res.push_back(*it);
    return res;
}


/**
 * @brief Returns a vector of strings stripped from both ends
 * 
 * @param word_list vector of strings
 * @param trim_list list of chars to be stripped
 * @return vector<string> 
 */
inline vector<string> strip(const vector<string> &word_list, const vector<char> &strip_list = vector<char>{' '}) {

    auto new_list = word_list;
    for (auto& word : new_list) 
        word = strip(word, strip_list);
    return new_list;
}


// Returns a vector of all primes numbers in range from 1 to _X (Max allowed _X = 2e9).
inline vector<int> primeListupto(int _X) {
    if (_X <= 1) return vector<int>();
    
    vector<bool> _arr(_X / 2 + 2);
    vector<int> prime_list(1, 2);
    const int sqrt_X = static_cast<int>(sqrt(_X)) + 1;

    // uses prime sieve
    for (int i = 0; (2 * i + 3) <= sqrt_X; i++)
        if (_arr[i] != 0)
            for (int j = 3 * i + 3; j <= _X / 2; j += 2 * i + 3)
                _arr[j] = true;
    
    for (int i = 0; 2 * i + 3 <= _X; i++)
        if (_arr[i] != 0)
            prime_list.emplace_back(2 * i + 3);
    
    return prime_list;
}

// Returns a vector of size __n with random values between low(inclusive) to high(exclusive).
template<typename _Tp> vector <_Tp>
random_array(size_t __n, _Tp low, _Tp high) {
    
    // Random Value Generator
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    auto rand_value_gen = [&] () mutable
        { return low + rng() % (high - low + 1); };

    vector <_Tp> random_values(__n);
    std::generate(begin(random_values), end(random_values), rand_value_gen);
    return random_values;
}


/**
 * @brief Returns a vector with no-repeated elements.
 * Does not preserves the order of elements.
 * 
 * @tparam _Tp
 * @param list 
 * @return vector<_Tp> 
 */
template<typename _Tp>
vector<_Tp> remove_duplicates(vector<_Tp> list) {

    if (list.empty())
        return vector<_Tp>();

    sort(begin(list), end(list));
    vector<_Tp> non_duplicated_list(1, list.front());

    for (const _Tp& value : list)
        if (non_duplicated_list.back() != value)
            non_duplicated_list.emplace_back(value);

    return non_duplicated_list;
}

/**
 * @brief Returns a vector with no-repeated elements.
 * Preserves the order of elements.
 * 
 * @tparam _Tp
 * @param list 
 * @return vector<_Tp> 
 */
template<typename _Tp>
vector<_Tp> remove_duplicates_with_order_preserve(const vector<_Tp>& list) {

    std::unordered_set<_Tp> unique_values;
    vector<_Tp> non_duplicated_list;

    for (const _Tp& value : list)
        unique_values.insert(value);

    for (const _Tp& value : list) {
        if (unique_values.find(value) == unique_values.end())
            continue;
        non_duplicated_list.emplace_back(value);
        unique_values.erase(value);
    }

    return non_duplicated_list;
}

// Returns a vector of digits of number (0th index represents unit place of number)
template<typename T>
vector<int> extract_digits(T _X) {
    if (_X == 0) return vector<int>(1, 0);
    _X = std::abs(_X);
    
    vector<int> res;
    while (_X) {
        res.emplace_back(_X % 10);
        _X /= 10;
    }
    return res;
}

// Returns a vector of all prime factors of _X.
template<typename T> 
vector<T> prime_factors_of(T _X) {
    vector<T> res;
    if ((_X & 1) == 0) {
        res.emplace_back(2);
        while ((_X & 1) == 0) _X >>= 1;
    }
    for (T i = 3; i * i <= _X; i += 2) {
        if (!(_X % i)) {
            res.emplace_back(i);
            while (!(_X % i)) _X /= i;
        }
    }

    if (_X > 1) res.emplace_back(_X);
    return res;
}

// Returns a vector of all factors of _X.
template<typename T> 
vector<T> factors_of(T _X, bool _sorted = true) {
    if (_X == (T)1) return vector<T>{1};
    vector<T> factors = {1, _X};
    for (T i = 2; i * i <= _X; i++) {
        if (!(_X % i)) {
            factors.emplace_back(i);
            if (i != _X / i) factors.emplace_back(_X / i);
        }
    }
    if (_sorted) sort(begin(factors), end(factors));
    return factors;
}

// Returns if a number is prime.
constexpr bool is_prime(size_t _X) {
    if (_X == 2) return true;
    if (_X < 2 || !(_X % 2)) return false;
    for (size_t i = 3; i * i <= _X; i += 2)
        if (!(_X % i)) return false;
    return true;
}

}

#endif

