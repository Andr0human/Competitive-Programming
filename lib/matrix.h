/**
 * @file matrix.h
 * @author Ayush Sinha
 * @brief Library for matrix operations in c++.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

using std::vector;
using std::string;
using std::cout;

#define RANDOM_STARTING_TIME std::chrono::steady_clock::now().time_since_epoch().count()

template <class _Tp = double>
class matrix {

private:

    vector<vector<_Tp>> mat;

    inline constexpr int digit_len(const _Tp value) const;

    inline const vector<string> split(const string &text, char sep = ' ');

    inline constexpr string dimension() const;

    inline constexpr bool array_dimension_mismatch(const vector<vector<string>> &nums) const;
    
    inline void set_default() { mat.resize(1, vector<_Tp>(1, 0)); }

public:

    inline matrix() = default;
    // inline matrix() { set_default(); }
    inline matrix(size_t __n)
    { mat.resize(__n, vector<_Tp>(__n, 0)); }

    inline matrix(size_t __n, size_t __m, _Tp value = 0)
    { mat.resize(__n, vector<_Tp>(__m, value)); }
    
    inline matrix(const vector<vector<_Tp>>& nums)
    : mat(nums) {}
    inline matrix(const vector<vector<_Tp>>&& nums)
    : mat(std::move(nums)) {}

    inline matrix(const matrix<_Tp>& other)
    : mat(other.mat) {}
    
    inline matrix(const matrix<_Tp>&& other)
    : mat(std::move(other.mat)) {}

    inline matrix(const vector<_Tp> &list, size_t col_size = 0);

    inline matrix(const string &str_nums);


    // UTILS

    inline constexpr size_t row_size() const { return mat.size(); }
    inline constexpr size_t col_size() const { return mat.empty() ? 0 : mat.back().size(); }
    inline constexpr std::pair<size_t, size_t> size() const { return std::make_pair(row_size(), col_size()); }

    // Returns the __nth row in matrix
    inline constexpr vector<_Tp> get(const size_t __n) const;

    // Returns the [__n][__m] element in matrix
    inline constexpr _Tp get(const size_t __n, const size_t __m) const;

    // Returns the elements of matrix in a vector
    inline constexpr vector<_Tp> tolist() const;
    
    // Returns the reference to __nth row in matrix
    inline vector<_Tp>& operator[] (const size_t __n);

    // Returns the transpose of matrix
    inline matrix transpose() const;

    // Prints the matrix
    inline void show() const;

    // Returns matrix from (r_start, c_start) to (r_end, c_end)
    inline matrix<_Tp> partition(size_t row_start, size_t row_end,
                               size_t col_start, size_t col_end) const;

    // Adds other matrix row-wise to the end of matrix
    inline void pad_rows(const matrix &other);

    // Adds other matrix column-wise to the end of matrix
    inline void pad_columns(const matrix &other);

    // ARITHMETIC

    inline void operator += (const matrix &_X);
    inline matrix operator+ (const matrix &_X) const;

    inline void operator -= (const matrix &_X);
    inline matrix operator- (const matrix &_X) const;

    inline matrix operator* (const matrix &_X) const;

};


#ifndef READ_WRITE

template <class _Tp>
inline matrix<_Tp>::matrix(const vector<_Tp> &list, size_t col_size) {

    const size_t l_size = list.size();
    if (!col_size) col_size = l_size;

    mat.resize(l_size / col_size + (l_size % col_size != 0), vector<_Tp>(col_size, 0));
    const auto &[n, m] = size();
    size_t cnt = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m && cnt < l_size; j++)
            mat[i][j] = list[cnt++];
}

template <class _Tp>
inline matrix<_Tp>::matrix(const string &str_nums) {
    
    const auto values = split(str_nums, ';');
    vector<vector<string>> nums;

    for (const auto &val : values) {
        const auto vec = split(val);
        if (vec.size()) nums.emplace_back(split(val));
    }


    if (nums.empty()) {
        set_default();
        return;
    }

    if (array_dimension_mismatch(nums))
        throw std::invalid_argument("2d array vertical dimensions mismatch!");

    mat.resize(nums.size(), vector<_Tp>(nums[0].size()));

    for (size_t i = 0; i < row_size(); i++)
        std::transform(begin(nums[i]), end(nums[i]), begin(mat[i]),
                       [](string const& val) { return std::stod(val); });

}

template<class _Tp>
inline void matrix<_Tp>::show() const {

    const auto abs_greater = [] (const _Tp &val1, const _Tp &val2) {
        return std::max(std::abs(val1), std::abs(val2));
    };

    const auto is_neg = [] (const _Tp &val) { return val < 0; };

    bool neg_el = false;
    vector<_Tp> m_vals(col_size());

    for (const auto &row : mat) {
        std::transform(begin(row), end(row), begin(m_vals),
                       begin(m_vals), abs_greater);
        if (!neg_el) neg_el = std::any_of(begin(row), end(row), is_neg);
    }

    for_each(begin(m_vals), end(m_vals), [&] (_Tp &val) { val = digit_len(val); } );

    const bool is_point_value = std::is_same<_Tp, double>() || std::is_same<_Tp, float>();

    const auto add_num_to_string = [&] (string &res, const _Tp val, const size_t __n) {

        int gap = *(begin(m_vals) + __n) + neg_el - (digit_len(val) + is_neg(val));
        while (gap--) res.push_back(' ');
        res += std::to_string(val);

        gap = 3;
        if (is_point_value)
            while (gap--) res.pop_back();

        if (__n != col_size() - 1) res += ", ";
    };


    std::cout << "[\n";
    for (const auto &row : mat) {
        string res = "\t[";

        for (auto it = begin(row); it != end(row); it++)
            add_num_to_string(res, *it, it - begin(row));

        res += "],\n";
        std::cout << res;
    }
    std::cout << "]\n" << std::flush;
}

template <class _Tp>
inline std::ostream& operator<< (std::ostream &stream, const matrix<_Tp> &mat) {
    mat.show();
    return stream;
}

#endif

#ifndef MATRIX_UTILS

template <class _Tp>
inline constexpr int matrix<_Tp>::digit_len(const _Tp value) const {

    // int64_t _X = static_cast<int64_t>(value);
    int _X = value;
    const long long lt = 1e14, m = 1e9, rt = 1e5;
    int res = 0;

    _X = _X >= 0 ? _X : -_X;
    res = _X >= m ? _X >= lt ? 14 : 9 : _X >= rt ?  5 : 0;
    _X /= _X >= m ? _X >= lt ? lt : m : _X >= rt ? rt : 1;
    res += _X > 999 ? _X > 9999 ? 5 : 4 : _X > 9 ? _X > 99 ? 3 : 2 : 1;
    return res;
}

template <class _Tp>
inline constexpr bool matrix<_Tp>::array_dimension_mismatch(const vector<vector<string>> &nums) const {
    const size_t c_size = nums[0].size();
    for (const auto &row : nums)
        if (row.size() != c_size) return true;
    return false;
}

template <class _Tp>
inline const vector<string> matrix<_Tp>::split(const string &__s, char sep) {

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

template <class _Tp>
inline constexpr string matrix<_Tp>::dimension() const {
    const auto &[row, col] = size();
    return std::string("(") + std::to_string(row) + std::string(", ")
         + std::to_string(col) + std::string(")");
}

template <class _Tp>
inline constexpr vector<_Tp> matrix<_Tp>::get(const size_t __n) const {
    if (__n >= mat.size())
        throw std::invalid_argument("Row out of range error!");
    return mat[__n];
}

template <class _Tp>
inline constexpr _Tp matrix<_Tp>::get(const size_t __n, const size_t __m) const {
    if (__n >= row_size() || __m >= col_size())
        throw std::invalid_argument("Element out of range error!");
    return mat[__n][__m];
}

template <class _Tp>
inline vector<_Tp>& matrix<_Tp>::operator[] (size_t x) {
    if (x >= row_size())
        throw std::invalid_argument("Out of range error!");
    return mat[x];
}

template <class _Tp>
inline constexpr vector<_Tp> matrix<_Tp>::tolist() const {
    vector<_Tp> res;
    res.reserve(row_size() * col_size());

    for (const auto &row : mat)
        res.insert(end(res), begin(row), end(row));

    return res;
}

template <class _Tp>
inline matrix<_Tp> matrix<_Tp>::transpose() const {

    const auto &[row, col] = size();
    matrix res(col, row);
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            res.mat[j][i] = mat[i][j];
    return res;
}

template <class _Tp>
inline matrix<_Tp> matrix<_Tp>::partition(size_t row_start, size_t row_end,
                                      size_t col_start, size_t col_end) const
{
    if (row_start > row_end)
        throw std::invalid_argument("row_end less than row_start error!");
    if (col_start > col_end)
        throw std::invalid_argument("col_end less than col_start error!");
    
    if (row_end > row_size() || (row_start == row_end && row_end == row_size()))
        throw std::invalid_argument("Row out of range error!");
    
    if (col_end > col_size() || (col_start == col_end && col_end == col_size()))
        throw std::invalid_argument("Column out of range error!");

    row_end += (row_start == row_end) ? 1 : 0;
    col_end += (col_start == col_end) ? 1 : 0;
    
    matrix<_Tp> res(row_end - row_start, col_end - col_start);

    for (size_t i = row_start; i < row_end; i++)
        std::copy(begin(mat[i]) + col_start, begin(mat[i]) + col_end,
                  begin(res[i - row_start]));

    return res;
}

template <class _Tp>
inline void matrix<_Tp>::pad_rows(const matrix<_Tp> &other) {
    if (col_size() != other.col_size())
        throw std::invalid_argument("Column mismatch in Row-padding!");

    mat.reserve(row_size() + other.row_size());

    for (const auto &row : other.mat)
        mat.emplace_back(row);

}

template <class _Tp>
inline void matrix<_Tp>::pad_columns(const matrix<_Tp> &other) {
    if (row_size() != other.row_size())
        throw std::invalid_argument("Row mismatch in column-padding!");

    for (size_t i = 0; i < row_size(); i++) {
        const auto &row = other.mat[i];
        mat[i].insert(end(mat[i]), begin(row), end(row));
    }

}

#endif

#ifndef MATRIX_ARITHMETIC

template <class _Tp>
inline void matrix<_Tp>::operator+= (const matrix<_Tp> &_X) {


    if (size() != _X.size()) {
        string error_msg = "Adding " + dimension() + " matrix with "
                                     + _X.dimension() + " matrix!";
        throw std::invalid_argument(error_msg);
    }

    const size_t n = row_size();
    for (size_t i = 0; i < n; i++)
        std::transform(begin(mat[i]), end(mat[i]), 
                       begin(_X.mat[i]), begin(mat[i]), std::plus<_Tp>());

}

template <class _Tp>
inline matrix<_Tp> matrix<_Tp>::operator+ (const matrix<_Tp> &_X) const {
    matrix ans = *this;
    ans += _X;
    return ans;
}

template <class _Tp>
inline void matrix<_Tp>::operator-= (const matrix<_Tp> &_X) {


    if (size() != _X.size()) {
        string error_msg = "Subtracting " + dimension() + " matrix with "
                                          + _X.dimension() + " matrix!";
        throw std::invalid_argument(error_msg);
    }


    const size_t n = row_size();
    for (size_t i = 0; i < n; i++)
        std::transform(begin(mat[i]), end(mat[i]), 
                       begin(_X.mat[i]), begin(mat[i]), std::minus<_Tp>());

}

template <class _Tp>
inline matrix<_Tp> matrix<_Tp>::operator- (const matrix<_Tp> &_X) const {
    matrix ans = *this;
    ans -= _X;
    return ans;
}

template <class _Tp>
inline matrix<_Tp> matrix<_Tp>::operator* (const matrix<_Tp> &_X) const {

    if (col_size() != _X.row_size()) {
        string error_msg = "Multiplying " + dimension() + " matrix with "
                                          + _X.dimension() + " matrix!";
        throw std::invalid_argument(error_msg);
    }

    const auto tp_X = _X.transpose().mat;
    matrix<_Tp> res(row_size(), _X.col_size());

    for (size_t i = 0; i < row_size(); i++)
        for (size_t j = 0; j < _X.col_size(); j++)
            res[i][j] = std::inner_product(begin(mat[i]), end(mat[i]),
                                           begin(tp_X[j]), res[i][j]);

    return res;
}


#endif


namespace matx {


/**
 * @brief Returns a (__n, __m) matrix with random values between low[inclusive] and high [exclusive]
 * 
 * @tparam _Tp 
 * @param __n 
 * @param __m 
 * @return matrix<_Tp> 
 */
template<class _Tp=double>
constexpr matrix<_Tp> rand(int __n, int __m = -1, int64_t low = 0, int64_t high = 1) {
    
    __m = (__m == -1) ? __n : __m;
    high += (low == high) ? 1 : 0;

    std::mt19937_64 rng(RANDOM_STARTING_TIME);


    auto rand_value = [=] () mutable {
        int64_t value1 = low + rng() % (high - low);
        double value2 = (double)rng() / rng.max();
        return (_Tp)value1 + value2;
    };

    vector<vector<_Tp>> res(__n, vector<_Tp>(__m));
    for (auto &row : res)
        for (auto &value : row)
            value = rand_value();

    return matrix<_Tp>(res);
}

// Returns the column-wise max of the matrix
template<class _Tp>
constexpr vector<_Tp> max(const matrix<_Tp> &mat) {

    // Checks for empty matrix

    const size_t n = mat.row_size();
    const size_t m = mat.col_size();

    auto res = mat.get(0);

    for (size_t i = 1; i < n; i++)
        for (size_t j = 0; j < m; j++)
            res[j] = std::max(res[j], mat.get(i, j));    

    return res;
}

// Returns the column-wise min of the matrix
template<class _Tp>
constexpr vector<_Tp> min(const matrix<_Tp> &mat) {

    // Checks for empty matrix

    const size_t n = mat.row_size();
    const size_t m = mat.col_size();

    auto res = mat.get(0);

    for (size_t i = 1; i < n; i++)
        for (size_t j = 0; j < m; j++)
            res[j] = std::min(res[j], mat.get(i, j));    

    return res;
}

// Returns an identity matrix of size __n
template<class _Tp=double>
constexpr matrix<_Tp> eye(size_t __n) {
    matrix<_Tp> res(__n);

    for (size_t i = 0; i < __n; i++)
        res[i][i] = 1;
    
    return res;
}


template<class _Tp>
constexpr matrix<_Tp> fast_mul(const matrix<_Tp> &a, const matrix<_Tp> &b) {
    
    if (a.row_size() < 128)
        return a * b;

    auto split_matrix = [] (const matrix<_Tp> &mt, matrix<_Tp> &p1, matrix<_Tp> &p2,
                                                 matrix<_Tp> &p3, matrix<_Tp> &p4) {

        const auto &[__r, __c] = mt.size();
        
        p1 = mt.partition(0, __r / 2, 0, __c / 2);
        p2 = mt.partition(0, __r / 2, __c / 2, __c);
        p3 = mt.partition(__r / 2, __r, 0, __c / 2);
        p4 = mt.partition(__r / 2, __r, __c / 2, __c);

    };

    auto join_matrix = [] (matrix<_Tp> &p1, matrix<_Tp> &p2,
                           matrix<_Tp> &p3, matrix<_Tp> &p4) {

        p1.pad_columns(p2);
        p3.pad_columns(p4);
        p1.pad_rows(p3);
    };


    matrix<_Tp> a1, a2, a3, a4;
    matrix<_Tp> b1, b2, b3, b4;
    matrix<_Tp> c1, c2, c3, c4;
    matrix<_Tp> p1, p2, p3, p4, p5, p6, p7;

    split_matrix(a, a1, a2, a3, a4);
    split_matrix(b, b1, b2, b3, b4);

    p1 = fast_mul(a1, b2 - b4);                                     // a1 * (b2 - b4);
    p2 = fast_mul(a1 + a2, b4);                                     // (a1 + a2) * b4;
    p3 = fast_mul(a3 + a4, b1);                                     // (a3 + a4) * b1;
    p4 = fast_mul(a4, b3 - b1);                                     // a4 * (b3 - b1);
    p5 = fast_mul(a1 + a4, b1 + b4);                                // (a1 + a4) * (b1 + b4);
    p6 = fast_mul(a2 - a4, b3 + b4);                                // (a2 - a4) * (b3 + b4);
    p7 = fast_mul(a1 - a3, b1 + b2);                                // (a1 - a3) * (b1 + b2);

    c1 = p5 + p4 - p2 + p6;
    c2 = p1 + p2;
    c3 = p3 + p4;
    c4 = p1 + p5 - p3 - p7;

    join_matrix(c1, c2, c3, c4);
    return c1;
}



}


#endif

