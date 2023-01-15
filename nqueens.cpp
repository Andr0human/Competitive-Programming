
/**
 * @file nqueens.cpp
 * @author Ayush Sinha
 * @brief
 * Solve 8 queens problems using bitwise operations and attack-tables.
 * 
 * 
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <array>
#include "lib/perf.h"

using std::array;
using std::cout;
using std::endl;


#ifndef NQUEENS_OLD


const size_t maxN = 30;

array<bool, maxN> column;
array<bool, 2 * maxN + 1> diag1;
array<bool, 2 * maxN + 1> diag2;

inline bool
is_marked(int row, int col, int __n)
{ return column[col] | diag1[row - col + __n] | diag2[row + col]; }

inline void place_queen(int row, int col, int __n)
{ column[col] = diag1[row - col + __n] = diag2[row + col] =  true; }

inline void unplace_queen(int row, int col, int __n)
{ column[col] = diag1[row - col + __n] = diag2[row + col] = false; }


uint64_t nqueens(int __n, int row = 0)
{
    if (row == __n)
        return 1;
    
    // node_counts++;
    
    uint64_t pos_found = 0;
    
    for (int col = 0; col < __n; ++col)
    {
        if (is_marked(row, col, __n))
            continue;
        
        place_queen(row, col, __n);
        pos_found += nqueens(__n, row + 1);
        unplace_queen(row, col, __n);
    }

    return pos_found;
}


#endif

#ifndef NQUEENS_NEW


array<uint64_t, 64> update_array;


inline int
lSb_idx(uint64_t __x)
{ return __builtin_ctzll(__x); }

void
generate_update_table()
{
    const auto in_range = [] (int __x)
    { return (__x >= 0) & (__x < 8); };

    const auto gen_value = [&] (int row, int col, int x, int y)
    {
        uint64_t res = 0;
        for (int i = row, j = col; in_range(i) and in_range(j); i += x, j += y)
            res |= 1ULL << (8 * i + j);

        return res;
    };

    auto& arr = update_array;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int sq = 8 * row + col;
            arr[sq] = gen_value(row, col, 0,  1)
                    | gen_value(row, col, 0, -1)
                    | gen_value(row, col, 1,  0)
                    | gen_value(row, col, 1,  1)
                    | gen_value(row, col, 1, -1);
        }
    }
}

void
bits_on_board(uint64_t value)
{
    std::string res;
    for (int row = 7; row >= 0; row--)
    {
        for (int col = 0; col < 8; col++)
        {
            if (value & (1ULL << (8 * row + col)))
                res.push_back('*');
            else
                res.push_back('.');
        }
        res.push_back('\n');
    }

    cout << res << endl;
}



uint64_t bit_nqueens(int queens, int __n, uint64_t board, uint64_t current_row)
{
    if (~board == 0)
        return (queens == 0);


    uint64_t pos_found = 0;
    uint64_t line = (~board) & current_row;

    while (line != 0)
    {
        int __pos = lSb_idx(line);
        line ^= 1ULL << __pos;

        uint64_t new_board = board | update_array[__pos];

        pos_found += bit_nqueens(queens - 1, __n, new_board, current_row << __n);
    }


    return pos_found;
}



#endif



int main()
{
    generate_update_table();

    puts("Task = (Nqueens 8 x 100'000)");

    double time_array = 0;
    double time_bit = 0;

    for (size_t cnt = 0; cnt < 100'000; cnt++)
    {
        time_array += perf::Time(nqueens, 8, 0);
        time_bit   += perf::Time(bit_nqueens, 8, 8, 0, (1 << 8) - 1);
    }

    cout << "Time_array = " << time_array << endl;
    cout << "Time_bit   = " << time_bit   << endl;

    cout << "IMP = " << time_array / time_bit << " x." << endl;
}

