
#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_set>

using std::vector;
using std::string;


namespace tools
{

// Maps every element of list to a new list using mapper_function.
template <typename _ListType, typename _UnaryOperation>
const auto
mapper(const std::vector<_ListType>& __list, _UnaryOperation __unary_op)
{
    // Generates a new_list using the return type of unary function.
    std::vector<__typeof__(__unary_op(__list.front()))>
        __mapped_list( __list.size() );

    // Map every element of __list to new_list using unary function.
    std::transform(begin(__list), end(__list),
                   begin(__mapped_list), __unary_op);
    return __mapped_list;
}


// Checks if a sequence is pallindromic
template<typename _RandomAccessIterator>
constexpr bool
is_pallindrome(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    size_t iters = (__last - __first) / 2;

    while (iters-- > 0)
    {
        --__last;

        // Compares the first element to last element in the list.
        if (*__first != *__last)
            return false;

        ++__first;
    }
    return true;
}


// Returns no. of digits in number _X.
constexpr int
len(int64_t _X)
{
    const int64_t lt = 1e14, m = 1e9, rt = 1e5;
    int _r = 0;

    _X = __builtin_llabs(_X);
    _r  = _X >= m ? _X >= lt ? 14 : 9 : _X >= rt ?  5 : 0;
    _X /= _X >= m ? _X >= lt ? lt : m : _X >= rt ? rt : 1;
    _r += _X > 999 ? _X > 9999 ? 5 : 4 : _X > 9 ? _X > 99 ? 3 : 2 : 1;
    
    return _r;
}


/**
 * @brief Returns A to power B.
 * Uses binary exponentiation.
 * @tparam _BaseType 
 * @tparam _ExpoType 
 * @param base 
 * @param expo 
 * @return constexpr _BaseType 
 */
template <typename _BaseType, typename _ExpoType>
constexpr _BaseType
pow(_BaseType base, _ExpoType expo)
{
    _BaseType res = 1;
    while (expo > 0)
    {
        res *= base * (expo & 1);
        expo >>= 1;
        base *= base;
    }
    return res;
}


/**
 * @brief Retuns A to the power B mod m.
 * 
 * @tparam _BaseType 
 * @tparam _ExpoType 
 * @tparam _ModType 
 * @param base 
 * @param expo 
 * @param mod 
 * @return constexpr _BaseType 
 */
template <typename _BaseType, typename _ExpoType, typename _ModType>
constexpr inline _BaseType
pow(_BaseType base, _ExpoType expo, _ModType mod)
{
    _BaseType res = 1;
    while (expo)
    {
        if (expo & 1) res = (res * base) % mod;
        expo >>= 1;
        base = (base * base) % mod;
    }
    return res;
}


// Returns the binary format for positive values for base 2 to 9.
inline string
bin(size_t num, size_t base = 2)
{
    if (num == 0)
        return string("0");
    
    string in_binary;
    while(num > 0)
    {
        in_binary.push_back(static_cast<char>(num % base) + '0');
        num /= base;
    }
    std::reverse(begin(in_binary), end(in_binary));
    return in_binary;
}


// Returns the least significant bit of an unsigned integer.
inline size_t
lSb(size_t __x)
{ return __x ^ (__x & (__x - 1)); }

// Returns the most significant bit of an unsigned integer.
inline size_t
mSb(size_t __x)
{ return __x != 0 ? (1ULL << (63 - __builtin_clzll(__x))) : 0; }

// Returns the number of set bits in an integer.
inline int
popCount(int32_t __x)
{ return __builtin_popcount(__x); }

// Returns the number of set bits in a long integer.
inline int
popCount(int64_t __x)
{ return __builtin_popcountll(__x); }


/**
 * @brief Extract and returns all elements from a single string.
 * 
 * @param __s String
 * @param sep separator
 * @return const vector<string> 
 */
inline vector<string>
split(const std::string &__s, const char sep)
{
    vector<string> res;
    size_t prev = 0, __n = __s.length();

    for (size_t i = 0; i < __n; i++)
    {
        if (__s[i] != sep)
            continue;
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
inline string
strip(const string &__s, const vector<char> &strip_list = vector<char>{' '})
{    
    if (__s.empty()) return __s;

    // Checks if a string element belongs to strip_list
    const auto in_strip_list = [&strip_list] (char ch)
    {
        return std::any_of(begin(strip_list), end(strip_list),
            [ch] (char val) { return val == ch; }
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
 * @brief Returns list of all prime no. between 2 to __x(inclusive).
 * Time Complexity : O(__x * log(log(__x)))
 * @tparam _Tp Return type of primelist (int, long long)
 * @param __x 
 * @return std::vector<_Tp> 
 */
template <typename _Tp = int>
vector<_Tp>
primelistupto(const size_t __x)
{
	if (__x < 2)
		return std::vector<_Tp>();		// 0 and 1 are non-primes.

	/**
	 * ith index represents number (2*i + 3).
	 * nums[i] == 0 => number at ith index is prime else non-prime.
	**/
	vector<bool> __pos((__x - 1) / 2);

	vector<_Tp> __prime_list(1, 2);

	const size_t __sqrt_x = static_cast<size_t>(sqrtl(__x)) + 1;
	const size_t __end = __pos.size();
	const _Tp __end_tp = static_cast<_Tp>(__end);

	// Algorithm uses prime sieve.

	for (size_t i = 0; (2*i + 3) <= __sqrt_x; i++)
    {
		if (__pos[i]) continue;	// number at ith __pos is non-prime

		size_t __inc = 2 * i + 3;
		size_t __start = ((__inc*__inc) - 3) / 2;

		for (size_t j = __start; j < __end; j += __inc)
			__pos[j] = true;				// Mark ith __pos to non-prime.
	}


	// Add marked primes indexes to a vector.
	for (_Tp i = 0; i < __end_tp; i++)
		if (__pos[i] == 0)
			__prime_list.emplace_back(2*i + 3);

	return __prime_list;
}


// Returns a vector of size __n with random values between low(inclusive) to high(exclusive).
template<typename _Tp>
vector <_Tp>
random_array(size_t __n, _Tp low, _Tp high)
{    
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
vector<_Tp>
remove_duplicates(vector<_Tp> __list)
{
    /**
     * @brief 
     * vector<int> nums{1, 4, 1, 2, 4, 7, 5, 5};
     * auto unique_nums = remove_duplicates(nums);
     * unique_nums => [1, 2, 4, 5, 7]
    **/

    if (__list.empty())
        return vector<_Tp>();

    // Sort the __list.
    sort(begin(__list), end(__list));

    // Create a new_list with the first element of __list.
    vector<_Tp> non_duplicated_list(1, __list.front());

    for (const _Tp& element : __list)
    {
        // If element in new_list, then ignore
        // otherwise add the element to new_list.
        if (non_duplicated_list.back() != element)
            non_duplicated_list.emplace_back(element);
    }

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
vector<_Tp>
remove_duplicates_with_order_preserve(const vector<_Tp>& __list)
{
    /**
     * @brief 
     * vector<int> nums{1, 4, 1, 2, 4, 7, 5, 5};
     * auto unique_nums = remove_duplicates_with_order_preserve(nums);
     * unique_nums => [1, 4, 2, 7, 5]
    **/

    std::unordered_set<_Tp> unique_values;
    vector<_Tp> non_duplicated_list;

    // Store all elements of list in a set.
    for (const _Tp& value : __list)
        unique_values.insert(value);

    for (const _Tp& value : __list)
    {
        /** If element is in set of unique_values,
         * add to new_list and remove element from list.
         * If element not in list, then element has
         * already accounted and should be ignored.
        **/
        if (unique_values.find(value) == unique_values.end())
            continue;

        non_duplicated_list.emplace_back(value);
        unique_values.erase(value);
    }

    return non_duplicated_list;
}

// Returns a vector of digits of number (0th index represents unit place of number)
vector<int>
extract_digits(size_t __x)
{
    if (__x == 0)
        return vector<int>(1, 0);
    
    vector<int> digits;
    while (__x)
    {
        digits.emplace_back(__x % 10);
        __x /= 10;
    }
    return digits;
}

/**
 * @brief
 * Returns a vector of all prime factors of __x.
 * default return_list_type if unsigned long long,
 * use prime_factors<int>(__x) to get list of int_type.
 * 
 * @tparam _Tp 
 * @param __x 
 * @return vector<_Tp> 
 */
template<typename _Tp = uint64_t>
vector<_Tp>
prime_factors(size_t __x)
{
    vector<_Tp> res;
    if ((__x & 1) == 0)
    {
        res.emplace_back(2);
        while ((__x & 1) == 0)
            __x >>= 1;
    }
  
    for (size_t i = 3; i * i <= __x; i += 2)
    {
        if ((__x % i) != 0) continue;
        res.emplace_back(i);
        while ((__x % i) == 0)
            __x /= i;
    }

    if (__x > 1)
        res.emplace_back(__x);
    return res;
}

// Returns a vector of all factors of _X.
template<typename _Tp = uint64_t> 
vector<_Tp>
factors(size_t __x)
{
    if (__x == 1ULL)
        return vector<_Tp>{1};

    vector<_Tp> factors = {1, __x};
    size_t __sqrt_x = static_cast<size_t>(sqrtl(__x)) + 1;

    if (__sqrt_x * __sqrt_x > __x)
    {
        --__sqrt_x;
        factors.emplace_back(__sqrt_x);
    }

    for (size_t i = 2; i < __sqrt_x; i++)
    {
        if (__x % i != 0) continue;
        factors.emplace_back(i);
        factors.emplace_back(__x / i);
    }
    std::sort(begin(factors), end(factors));
    return factors;
}

/**
 * @brief Returns if __x is prime.
 * Time Complexity : O(sqrt(__x))
 * 
 * @param __x 
 * @return true 
 * @return false 
 */
constexpr bool
is_prime(size_t __x)
{
    if (__x == 2)
        return true;

    if (__x < 2 || (__x % 2) == 0)
        return false;

    // Check if __x is divisible by a odd number in range[3, sqrt(__x)].
    for (size_t i = 3; i * i <= __x; i += 2)
        if ((__x % i) == 0) return false;

    return true;
}

}

#endif

