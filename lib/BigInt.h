/**
 * @file BigInt.h
 * @author Ayush Sinha
 * @brief BigInt library for arithmetic aned bitwise operations on large numbers.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BIGINT_H
#define BIGINT_H


#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>
#include <chrono>


/**
 * @Todo = Division
 * 
 */


class BigInt
{
	typedef 				uint32_t 	_Digit_Type;
	typedef std::vector<_Digit_Type> 	 __bigvec__;

private:
	const static _Digit_Type BITS_PER_WORD = 32;
	const static _Digit_Type WORD_MAX_VALUE = (1ULL << BITS_PER_WORD) - 1;

	// Stores elements of number.
	__bigvec__ digits;

	// __sign is true if number is positive else false.
	bool __sign;


	#ifndef BIGINT_UTILS

	void
	set_to_value (const uint32_t value)
	{ digits = __bigvec__{value}; }

	void
	set_to_value (const uint64_t value)
	{
		const _Digit_Type __l = static_cast<_Digit_Type>(value >> BITS_PER_WORD);
		const _Digit_Type __r = static_cast<_Digit_Type>(value & WORD_MAX_VALUE);

		digits = __l > 0 ? __bigvec__{__r, __l} : __bigvec__{__r};
	}

	void
	set_to_value (const int32_t value)
	{
		uint32_t _X = static_cast<uint32_t>(value);
		_X = (_X ^ (WORD_MAX_VALUE * (__sign ^ 1))) + (__sign ^ 1);
		set_to_value(_X);
	}

	void
	set_to_value (const int64_t value)
	{
		uint64_t _X = static_cast<uint64_t>(value);
		_X = (_X ^ (ULLONG_MAX * (__sign ^ 1))) + (__sign ^ 1);
		set_to_value(_X);
	}

	bool
	is_zero() const noexcept
	{ return digits.size() == 1 && digits.front() == 0; }

	void
	remove_trailing_zeros() noexcept
	{
		while (digits.size() > 1 && digits.back() == 0)
			digits.pop_back();
		if (digits.size() == 1 && digits.front() == 0)
			__sign = true;
	}

	static std::string
	multiply(const std::string& __s, uint64_t multiplier)
	{
		uint64_t carry = 0;
		std::string res;

		for (auto& value : __s)
		{
			carry += (value - '0') * multiplier;
			res.push_back(static_cast<char>(carry % 10) + '0');
			carry /= 10;
		}

		while (carry > 0)
		{
			res.push_back(static_cast<char>(carry % 10) + '0');
			carry /= 10;
		}

		return res;
	}

	static void
	arithmetic_add_strings (std::string& s1, const std::string& s2)
	{
		size_t __n = s2.length();

		while (s1.length() < __n)
			s1.push_back('0');

		uint32_t carry = 0;
		for (size_t i = 0; i < __n; i++)
		{
			carry += (s1[i] - '0') + (s2[i] - '0');
			s1[i] = static_cast<char>(carry % 10) + '0';
			carry /= 10;
		}

		while (carry > 0 && __n < s1.length())
		{
			carry += s1[__n] - '0';
			s1[__n++] = static_cast<char>(carry % 10) + '0';
			carry /= 10;
		}

		while (carry > 0)
		{
			s1.push_back(static_cast<char>(carry % 10) + '0');
			carry /= 10;
		}

		while (s1.length() > 1 && s1[s1.length() - 1] == '0')
			s1.pop_back();
	}

	static void
	bitwise_rightshift_16_on_decimal(std::vector<uint64_t>& A) noexcept
	{
		const uint32_t right_shift = 16;
		const uint64_t FILTER = (1 << 16) - 1;

		uint64_t updater_value = 0, c = 0;
		const uint64_t p1 = static_cast<uint64_t>(1e16) >> right_shift;

		const auto update_element = [&] (uint64_t& __x)
		{
			c = __x;
			__x = updater_value * p1 + (c >> right_shift);
			updater_value = c & FILTER;
		};

		for_each(rbegin(A), rend(A), update_element);
		while (!A.empty() && A.back() == 0) A.pop_back();
	}

	static std::vector<uint64_t>
	string_to_vector(const std::string& __s, const size_t __digits_per_word)
	{
		const size_t __n = __s.length();

		size_t start  = __s[0] == '-';
		size_t extra_len = (__n - start) % __digits_per_word;

		std::vector<uint64_t> in_decimal(
			(__n - start) / __digits_per_word + (extra_len != 0)
		);
		auto __rf = rbegin(in_decimal);

		const auto add_to_vector = [&__rf, &__s] (size_t& current, size_t end) 
		{
			for (; current < end; ++current)
				*__rf = *__rf * 10 + (__s[current] - '0');
			++__rf;
		};

		if (extra_len != 0)
			add_to_vector(start, start + extra_len);

		while (start < __n)
			add_to_vector(start, start + __digits_per_word);

		return in_decimal;
	}

	#endif


	#ifndef BIGINT_BITS_ARITHMETIC


	void
	bits_adder(const BigInt& other)
	{
		if (digits.size() < other.digits.size())
			digits.resize(other.digits.size());

		const auto __n2 = other.digits.size();
		uint64_t carry = 0;
		
		const auto adder = [&carry] (uint64_t __x, uint64_t __y = 0) {
			carry = carry + __x + __y;
			const auto res = static_cast<uint32_t>(carry & WORD_MAX_VALUE);
			carry >>= BITS_PER_WORD;
			return res;
		};

		std::transform(begin(other.digits), end(other.digits),
			begin(digits), begin(digits), adder);

		std::transform(begin(digits) + __n2, end(digits),
			begin(digits) + __n2, adder);

		if (carry > 0)
			digits.emplace_back(carry);
	}


	void
	bits_subtracter(const BigInt& other)
	{
		// Works if self is greater than other.

		auto __f1 = begin(digits);
		auto __f2 = begin(other.digits);
		auto __e2 = end(other.digits);

		for (; __f2 != __e2; ++__f1, ++__f2)
		{
			if (*__f1 >= *__f2) {
				*__f1 = *__f1 - *__f2;
				continue;
			}

			*__f1 = *__f1 + (WORD_MAX_VALUE - *__f2) + 1;
			auto __g = __f1 + 1;
			for (; *__g == 0; ++__g) *__g = WORD_MAX_VALUE - 1;
			(*__g)--;
		}

		remove_trailing_zeros();
	}


	void
	bits_multiplier (const BigInt &other)
	{
		const uint64_t __n1 = digits.size();
		const uint64_t __n2 = other.digits.size();

		const uint64_t FILTER = static_cast<uint64_t>(WORD_MAX_VALUE);
		const uint64_t update_interval = (1ULL << 15) - 1;

		std::vector<uint64_t> answer(__n1 + __n2 + 2);

		const auto update_answer_array = [&answer] ()
		{
			uint64_t carry = 0;
			std::transform(begin(answer), end(answer), begin(answer),
				[&carry] (uint64_t __x)
				{
					carry += __x;
					__x = carry & WORD_MAX_VALUE;
					carry >>= BITS_PER_WORD;
					return __x;
				}
			);
		};

		for (size_t i = 0; i < __n1; i += 2)
		{
			uint64_t x0 = digits[i];
	        uint64_t x1 = (i == __n1 - 1 ? 0 : digits[i + 1]);

			for (size_t j = 0; j < __n2; j++)
			{
				uint64_t w0 = x0 * other.digits[j];
				uint64_t w1 = x1 * other.digits[j];

				answer[i + j] += w0 & FILTER;
				uint64_t extra = w1 + (w0 >> BITS_PER_WORD);

				answer[i + j + 1] += extra & FILTER;
				answer[i + j + 2] += extra >> BITS_PER_WORD;
			}

			if ((i & update_interval) == 0)
				update_answer_array();
		}

		update_answer_array();
		digits.resize(answer.size() - 2);

		std::transform(begin(answer), end(answer) - 2, begin(digits),
			[] (uint64_t __x) {
				return static_cast<uint32_t>(__x);
			}
		);

		remove_trailing_zeros();
		__sign = __sign ^ other.__sign ^ 1;
	}


	#endif

	#ifndef BIGINT_KARATSUBA_MULTIPLY

	BigInt
	normal_multiply(const BigInt& other) const noexcept
	{
		BigInt res = *this;
		res.bits_multiplier(other);
		return res;
	}

	static void
	half_split(const BigInt& _X, BigInt& _A, BigInt& _B, size_t half_B)
	{
		const size_t __n = _X.digits.size();
		half_B = std::min(half_B, __n);

		size_t half_A = __n - half_B;

		if (half_A > 0) _A.digits.resize(half_A);
		if (half_B > 0) _B.digits.resize(half_B);

		std::copy(begin(_X.digits), begin(_X.digits) + half_B, begin(_B.digits));
		std::copy(begin(_X.digits) + half_B,   end(_X.digits), begin(_A.digits));
	}

	BigInt
	karatsuba_multiply(const BigInt& _X) const
	{
		const size_t __n1 = digits.size();
		const size_t __n2 = _X.digits.size();
		const size_t halfpoint = std::max(__n1, __n2) / 2;

		if (__n1 * __n2 <= 5000ULL) return normal_multiply(_X);

		BigInt a, b, c, d, ac, bd, ad_bc;

	    half_split(*this, a, b, halfpoint);
	    half_split(   _X, c, d, halfpoint);

	    ac = a.karatsuba_multiply(c);
    	bd = b.karatsuba_multiply(d);
    	ac.__sign = bd.__sign = 1;

	    ad_bc = (a + b).karatsuba_multiply(c + d) - (ac + bd);
	    ad_bc.__sign = 1;

	    return (ac << (halfpoint * 64)) + (ad_bc << (halfpoint * 32)) + bd;
	}


	#endif


	public:
	#ifndef BIGINT_FUNCTIONS

	static BigInt
	random(size_t low = 1, size_t high = 64)
	{
		std::mt19937 rng32(static_cast<uint32_t>(
			std::chrono::steady_clock::now().time_since_epoch().count()));

		high = std::max(low, high);
		size_t length = low + rng32() % (high - low + (high == low));
		size_t units = length / BITS_PER_WORD + (length % BITS_PER_WORD != 0);

		BigInt random_value;
		random_value.digits.resize(units);

		std::generate(begin(random_value.digits),
			end(random_value.digits), rng32);

		return random_value;
	}

	void
	print() const
	{
		auto __f = rbegin(digits);
		auto __e = rend(digits);

		for (; __f != __e; ++__f)
			std::cout << *__f << ' ';
		std::cout << std::endl;
	}

	static void
	print(const std::vector<uint64_t>& vect)
	{
		auto __f = rbegin(vect);
		auto __e = rend(vect);

		for (; __f != __e; ++__f)
			std::cout << *__f << ' ';
		std::cout << std::endl;
	}

	#endif

	_Digit_Type
	get(size_t __pos) const
	{ return digits[__pos]; }

	BigInt ()
	: digits(__bigvec__(1, 0)), __sign(true) {}

	template <typename _Tp>
	BigInt (const _Tp value)
	: __sign (value >= 0) { set_to_value(value); }


	bool
	invalid_string_constructor (const std::string& __s) const
	{
		const auto is_out_of_zero_to_nine = [] (char ch) {
			return !(ch >= '0' && ch <= '9');
		};

		if (__s.empty()) return true;

		auto __f = begin(__s);
		auto __e = end(__s);

		if (*__f == '-') ++__f;

		if ((__f == __e) ||
			!(*__f > '0' && *__f <= '9')) return true;

		for (; __f != __e; ++__f)
			if (is_out_of_zero_to_nine(*__f)) return true;

		return false;
	}


	BigInt(const std::string& __s)
	{
		if (invalid_string_constructor(__s))
			throw std::invalid_argument("Invalid string passed as contructor!");

		__sign = __s[0] != '-';

		auto in_decimal = string_to_vector(__s, 16);
		int adder = 0;

		while (!in_decimal.empty())
		{
			uint64_t value = in_decimal.front();
			uint32_t in_binary = 0;
			
			for (int j = 0; j < 16; j++)
				in_binary += static_cast<uint32_t>(value & (1ULL << j));

			if (adder == 0)
				digits.emplace_back(in_binary);
			else
				digits.back() = (in_binary << 16) + digits.back();

			adder ^= 1;
			bitwise_rightshift_16_on_decimal(in_decimal);
		}
	}


	#ifndef BIGINT_UTILS

	bool
	is_bit(size_t __pos) const noexcept
	{ return (digits[__pos >> 5] & (1U << (__pos & 31))) != 0; }

	std::string
	str() const
	{
		if (digits.size() == 1)
			return std::string(__sign ? "" : "-") + std::to_string(digits[0]);

		uint64_t value = digits[0]
			+ (static_cast<uint64_t>(digits[1]) << BITS_PER_WORD);

		std::string res = std::to_string(value);
		if (digits.size() == 2)
			 return std::string(__sign ? "" : "-") + res;

		std::string a = "61615590737044764481";			// 2 ** 64 in reverse
		std::reverse(begin(res), end(res));
		
		for (size_t i = 2; i < digits.size(); i++)
		{
			arithmetic_add_strings(res, multiply(a, digits[i]));
			a = multiply(a, 1ULL << 32);
		}

		if (!__sign) res.push_back('-');
		std::reverse(begin(res), end(res));
		return res;
	}

	size_t
	max_bit() const noexcept
	{
		return (32 * (digits.size() - 1))
			+ (__builtin_clz(digits.back() | 1) ^ 31);
	}


	#endif


	#ifndef BIGINT_COMPARATORS

	bool
	greater_than(const BigInt& other) const noexcept
	{
		if (digits.size() > other.digits.size()) return true;
		if (digits.size() < other.digits.size()) return false;

		auto __f1 = rbegin(digits);
		auto __f2 = rbegin(other.digits);
		auto __e1 = rend(digits);

		for (; __f1 != __e1; ++__f1, ++__f2)
		{
			if (*__f1 > *__f2) return true;
			if (*__f1 < *__f2) return false;
		}

		return false;
	}

	bool
	smaller_than(const BigInt& other) const noexcept
	{
		if (digits.size() < other.digits.size()) return true;
		if (digits.size() > other.digits.size()) return false;

		auto __f1 = rbegin(digits);
		auto __f2 = rbegin(other.digits);
		auto __e1 = rend(digits);

		for (; __f1 != __e1; ++__f1, ++__f2)
		{
			if (*__f1 < *__f2) return true;
			if (*__f1 > *__f2) return false;
		}

		return false;
	}

	bool
	operator>(const BigInt& other) const noexcept
	{
		if (__sign > other.__sign) return true;
		if (__sign < other.__sign) return false;
		if (__sign) return greater_than(other);
		return smaller_than(other);
	}

	bool
	operator<(const BigInt& other) const noexcept
	{
		if (__sign > other.__sign) return false;
		if (__sign < other.__sign) return true;
		if (!__sign) return greater_than(other);
		return smaller_than(other);
	}

	bool
	operator>=(const BigInt& other) const noexcept
	{ return !(*this < other); }
	
	bool
	operator<=(const BigInt& other) const noexcept
	{ return !(*this > other); }

	bool
	operator==(const BigInt& other) const noexcept
	{
		if ( (__sign != other.__sign) ||
			digits.size() != other.digits.size() ) return false;
		
		auto __f1 = rbegin(digits);
		auto __f2 = rbegin(other.digits);
		auto __e1 = rend(digits);

		for (; __f1 != __e1; ++__f1, ++__f2)
			if (*__f1 != *__f2) return false;
		
		return true;
	}
	
	bool
	operator!=(const BigInt& other) const noexcept
	{ return !(*this == other); }

	#endif


	#ifndef BIGINT_BITWISE_OPERATORS

	void
	operator^=(const BigInt& other) noexcept
	{
		if (digits.size() < other.digits.size())
			digits.resize(other.digits.size());

		std::transform(begin(other.digits), end(other.digits),
			begin(digits), begin(digits), std::bit_xor<_Digit_Type>());

		remove_trailing_zeros();
	}

	BigInt
	operator^(const BigInt& other) const noexcept
	{
		auto& larger_value  = digits.size() >= other.digits.size() ? *this : other;
		auto& smaller_value = digits.size()  < other.digits.size() ? *this : other;

		BigInt res = larger_value;
		res ^= smaller_value;
		return res;
	}

	void
	operator&=(const BigInt& other) noexcept
	{
		if (digits.size() > other.digits.size())
			digits.resize(other.digits.size());
		
		std::transform(begin(digits), end(digits),
			begin(other.digits), begin(digits), std::bit_and<_Digit_Type>());
	}

	BigInt
	operator&(const BigInt& other) const noexcept
	{
		auto& larger_value  = digits.size() >= other.digits.size() ? *this : other;
		auto& smaller_value = digits.size()  < other.digits.size() ? *this : other;

		BigInt res = smaller_value;
		res &= larger_value;
		return res;
	}

	void
	operator|=(const BigInt& other) noexcept
	{
		if (digits.size() < other.digits.size())
			digits.resize(other.digits.size());

		std::transform(begin(digits), end(digits),
			begin(other.digits), begin(digits), std::bit_or<_Digit_Type>());
	}

	BigInt
	operator|(const BigInt& other) const noexcept
	{
		auto& larger_value  = digits.size() >= other.digits.size() ? *this : other;
		auto& smaller_value = digits.size()  < other.digits.size() ? *this : other;

		BigInt res = larger_value;
		res |= smaller_value;
		return res;
	}

	void
	operator<<=(const size_t __x) noexcept
	{
		if (is_zero()) return;

		const size_t f_shift = __x >> 5;
		const size_t e_shift = __x & (BITS_PER_WORD - 1);

		const uint32_t r_side = (1 << (BITS_PER_WORD - e_shift)) - 1;
		const uint32_t l_side  = WORD_MAX_VALUE ^ r_side;

		uint32_t carry = 0;

		const auto updater = [&] (uint32_t value) {
			const uint32_t new_value = ((value & r_side) << e_shift) | carry;
			carry = (value & l_side) >> (BITS_PER_WORD - e_shift);
			return new_value;
		};

		if (e_shift != 0)
			std::transform(begin(digits), end(digits), begin(digits), updater);

		size_t __n = static_cast<uint32_t>(digits.size());
		size_t new_size = __n + f_shift + (carry > 0);

		if (new_size == __n) return;

		digits.resize(new_size);
		if (carry > 0) digits[__n] = carry;

		std::copy(begin(digits),   end(digits) - f_shift, begin(digits) + f_shift);
		std::fill(begin(digits), begin(digits) + f_shift, 0);
	}

	BigInt
	operator<<(const size_t __x) const noexcept
	{
		BigInt res = *this;
		res <<= __x;
		return res;
	}

	void
	operator>>=(const size_t __x) noexcept
	{
		if (is_zero()) return;

		const size_t f_shift = __x >> 5;
		const size_t e_shift = __x & (BITS_PER_WORD - 1);

		const uint32_t r_side = (1 << e_shift) - 1;
		// const uint32_t l_side  = WORD_MAX_VALUE ^ r_side;

		if (f_shift > 0) {
			std::copy(begin(digits) + f_shift, end(digits), begin(digits));
	    	digits.resize(digits.size() - f_shift);
		}

    	uint32_t carry = 0;

    	const auto updater = [&] (uint32_t& value) {
    		uint32_t new_value = (value >> e_shift) | (carry << (BITS_PER_WORD - e_shift));
    		carry = value & r_side;
    		return new_value;
    	};

    	if (e_shift != 0)
    		std::transform(rbegin(digits), rend(digits), rbegin(digits), updater);
    	remove_trailing_zeros();
	}

	BigInt
	operator>> (const size_t __x) const noexcept
	{
		BigInt res = *this;
		res >>= __x;
		return res;
	}

	#endif


	#ifndef BIGINT_ARITHMETIC_ADD

	void
	operator+=(const BigInt& other) noexcept
	{
		if (__sign == other.__sign)
			return bits_adder(other);

		if (smaller_than(other) == false)
			return bits_subtracter(other);

		const auto to_subtract = *this;
		*this = other;
		bits_subtracter(to_subtract);
	}

	BigInt
	operator+(const BigInt& other) const noexcept
	{
		auto& larger_value  = digits.size() >= other.digits.size() ? *this : other;
		auto& smaller_value = digits.size()  < other.digits.size() ? *this : other;

		BigInt res = larger_value;
		res += smaller_value;
		return res;
	}

	#endif


	#ifndef BIGINT_ARITHMETIC_SUBTRACT

	void
	operator-=(const BigInt& other) noexcept
	{
		if (__sign == other.__sign)
		{
			if (smaller_than(other) == false)
				return bits_subtracter(other);

			auto to_subtract = *this;
			*this = other;
			__sign ^= 1;
			return bits_subtracter(to_subtract);
		}

		return bits_adder(other);
	}

	BigInt
	operator-(const BigInt& other) const noexcept
	{
		BigInt res = *this;
		res -= other;
		return res;
	}

	#endif


	#ifndef BIGINT_ARITHMETIC_MULTIPLY

	void
	operator*=(const BigInt& other) noexcept
	{
		bool ans_sign = __sign ^ other.__sign ^ 1;
		*this = karatsuba_multiply(other);
		__sign = ans_sign;
	}

	BigInt
	operator*(const BigInt& other) const noexcept
	{
		BigInt res = karatsuba_multiply(other);
		res.__sign = __sign ^ other.__sign ^ 1;
		return res;
	}


	#endif


	#ifndef BIGINT_ARITHMETIC_DIVIDE

/* 	void
	operator/=(const BigInt& other) {

		if (other.is_zero())
			throw std::invalid_argument("Divide by Zero Error!");

		if (smaller_than(other))
			return set_to_value(0);

	} */

	#endif
};


inline std::ostream&
operator<<(std::ostream &stream, const BigInt& num)
{
    stream << num.str();
    return stream;
}




#endif


