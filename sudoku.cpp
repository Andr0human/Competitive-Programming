/**
 * @file sudoku.cpp
 * @author Ayush Sinha
 * @brief 
 * Sodoku Solver
 * 
 * -> sudoku solve 'position' :- Find and print solution if the position is valid.
 * -> sudoku count 'position' :- Counts total no. of solution for any position.
 * 
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <cstdint>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

using _Data_Type = int32_t;

namespace tools
{

std::chrono::_V2::high_resolution_clock::time_point tmp_clock_startpoint;

inline int
pop_count(uint64_t x)
{
    const uint64_t m1  = 0x5555555555555555;
    const uint64_t m2  = 0x3333333333333333;
    const uint64_t m4  = 0x0f0f0f0f0f0f0f0f;
    const uint64_t h01 = 0x0101010101010101;
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4; 
    return static_cast<int>((x * h01) >> 56);
}

inline int
ctz(uint64_t x)
{ return pop_count((x & -x) - 1); }

inline int
next_idx(_Data_Type &__n)
{
    // const int res = __builtin_ctz(__n) + 1;
    const int res = ctz(__n) + 1;
    __n &= __n - 1;
    return res;
}

inline void
start_clock()
{ tmp_clock_startpoint = std::chrono::high_resolution_clock::now(); }

inline double
end_clock()
{
    std::chrono::duration<double> dur
        = std::chrono::high_resolution_clock::now() - tmp_clock_startpoint;
    return dur.count();
}


}


class sudoku_board
{
    private:
    using _Marked_Value_Array = std::array<_Data_Type, 9>;
    const static _Data_Type ALL = 511;

    std::array<_Data_Type, 81> board;
    
    _Marked_Value_Array row_array;
    _Marked_Value_Array column_array;
    _Marked_Value_Array block_array;

    inline size_t
    ref_row(size_t __pos) const noexcept
    { return __pos / 9; }

    inline size_t
    ref_col(size_t __pos) const noexcept
    { return __pos % 9; }

    inline size_t
    ref_block(size_t row, size_t col) const noexcept
    { return 3 * static_cast<size_t>(row / 3) + col / 3; }

    inline void
    reset() noexcept
    {
        row_array.fill(0);
        column_array.fill(0);
        block_array.fill(0);
        board.fill(0);
    }

    public:
    inline
    sudoku_board() noexcept
    { reset(); }

    inline
    sudoku_board(const std::string& __s)
    {    
        if (__s.size() > 81)
            throw std::invalid_argument("Invalid Sudoku!!");

        reset();

        for (size_t idx = 0; idx < __s.size(); idx++)
        {
            const _Data_Type num = static_cast<_Data_Type>(__s[idx]) - 48;
            board[idx] = num;
            if (num != 0) mark(idx, num);
        }
    }

    inline bool
    empty(size_t square_no) const noexcept
    { return board[square_no] == 0; }

    inline void
    mark(const size_t square_no, const int num)
    {
        const _Data_Type value = 1 << (num - 1);
        const size_t __r = ref_row(square_no);
        const size_t __c = ref_col(square_no);
        const size_t __b = ref_block(__r, __c);

        row_array[__r] |= value;
        column_array[__c] |= value;
        block_array[__b] |= value;

        board[square_no] = num;
    }

    inline void
    unmark(const size_t square_no, const int num)
    {
        const _Data_Type value = ALL ^ (1 << (num - 1));
        const size_t __r = ref_row(square_no);
        const size_t __c = ref_col(square_no);
        const size_t __b = ref_block(__r, __c);

        row_array[__r] &= value;
        column_array[__c] &= value;
        block_array[__b] &= value;

        board[square_no] = 0;
    }

    inline _Data_Type
    unmarked_values(const std::size_t square_no) const noexcept
    {
        const size_t __r = ref_row(square_no);
        const size_t __c = ref_col(square_no);
        const size_t __b = ref_block(__r, __c);
        return ALL ^ (row_array[__r] | column_array[__c] | block_array[__b]);
    }

    void
    show() const
    {
        using std::cout;

        const std::string s = " +-------------+-----------+-------------+\n";
        const std::string g1 = " || ";
        const std::string g2 = " | ";

        cout << s;

        for (int row = 0; row < 9; ++row)
        {
            cout << g1;
            for (int col = 0; col < 9; ++col) {
                cout << board[9 * row + col];
                cout << ((col != 0 && col % 3 == 2) ? (g1) : (g2));
            }
            cout << '\n' << s;
            if (row != 0 && row != 8 && row % 3 == 2) cout << s;
        }
        cout << std::endl;
    }

    inline std::string
    str() const noexcept
    {
        std::string res;
        res.resize(81);

        for (int i = 0; i < 81; i++)
            res[i] = static_cast<char>(board[i] + '0');

        return res;
    }

    inline _Data_Type
    row(int idx) const noexcept
    { return row_array[idx]; }

    inline _Data_Type
    column(int idx) const noexcept
    { return column_array[idx]; }

    inline _Data_Type
    block(int idx) const noexcept
    { return block_array[idx]; }

    inline _Data_Type
    value_at_square(const int square) const noexcept
    { return board[square]; }

    inline _Data_Type
    all() const noexcept
    { return ALL; }
};


namespace sudoku
{

namespace search_optimisations
{

inline bool block_validity_check
(sudoku_board& __pos, _Data_Type left_values, int col)
{    
    _Data_Type x = left_values & __pos.column(col);
    _Data_Type y = left_values & __pos.column(col + 1);
    _Data_Type z = left_values & __pos.column(col + 2);

    _Data_Type u = x & y;
    _Data_Type v = y & z;
    _Data_Type w = x & z;
    
    return ((u & (u - 1))
          | (v & (v - 1))
          | (w & (w - 1))) == 0;
}

inline uint64_t square_66_cut(sudoku_board& __pos, _Data_Type l_row2)
{
    _Data_Type l_row1 = __pos.block(6);
    _Data_Type block6 = l_row1 | l_row2;
    _Data_Type l_row3 = __pos.all() ^ block6;

    _Data_Type m_row1 = __pos.block(7);
    _Data_Type m_row2 = l_row3 ^ (l_row3 & m_row1);

    int left = tools::pop_count(m_row2);

    if (left == 0)
        return block_validity_check(__pos, l_row1, 3)
             & block_validity_check(__pos, l_row3, 6);
    if (left == 3)
        return block_validity_check(__pos, m_row2, 3)
             & block_validity_check(__pos, l_row1, 6);

    _Data_Type m_col1 = __pos.all() ^ __pos.column(3);
    _Data_Type m_col2 = __pos.all() ^ __pos.column(4);
    _Data_Type m_col3 = __pos.all() ^ __pos.column(5);
    _Data_Type m_row3 = l_row2 ^ (l_row2 & m_row1);


    _Data_Type c_row = left == 2 ? m_row2 : m_row3;
    _Data_Type rem = ((c_row & m_col1) == 0) ? (m_col1) :
                    (((c_row & m_col2) == 0) ? (m_col2) : (m_col3));

    rem = rem ^ (rem & l_row2);

    m_row2 = (left == 2) ? (m_row2)
           : __pos.all() ^ (m_row3 | __pos.block(7) | rem);
    
    _Data_Type rem1 = rem & (rem - 1);
    _Data_Type rem2 = rem ^ rem1;
    _Data_Type value1 = m_row2 | rem1;
    _Data_Type value2 = m_row2 | rem2;

    _Data_Type s_value1 = __pos.all() ^ (l_row2 | value1);
    _Data_Type s_value2 = __pos.all() ^ (l_row2 | value2);

    uint64_t ans = 0;

    if ((l_row2 & value1) == 0)
        ans += block_validity_check(__pos, value1, 3)
             & block_validity_check(__pos, s_value1, 6);
    
    if ((l_row2 & value2) == 0)
        ans += block_validity_check(__pos, value2, 3)
             & block_validity_check(__pos, s_value2, 6);
    
    return ans;
}

inline uint64_t square_63_cut(sudoku_board& __pos)
{
    const auto solution =
        [&__pos] (_Data_Type a, _Data_Type b, _Data_Type c)
    {
        const _Data_Type value = a | b | c;
        return square_66_cut(__pos, value);
    };

    _Data_Type x = __pos.all() ^ __pos.column(0);
    _Data_Type y = __pos.all() ^ __pos.column(1);
    _Data_Type z = __pos.all() ^ __pos.column(2);

    const _Data_Type x1 = x & (x - 1), x2 = x ^ x1;
    const _Data_Type y1 = y & (y - 1), y2 = y ^ y1;
    const _Data_Type z1 = z & (z - 1), z2 = z ^ z1;

    return solution(x1, y1, z1) + solution(x1, y1, z2)
         + solution(x1, y2, z1) + solution(x1, y2, z2)
         + solution(x2, y1, z1) + solution(x2, y1, z2)
         + solution(x2, y2, z1) + solution(x2, y2, z2);

}

inline uint64_t square_60_cut(sudoku_board& __pos)
{
    _Data_Type left_vals = __pos.all() ^ __pos.row(6);

    if (!block_validity_check(__pos, left_vals, 6)) return 0;

    int v1 = tools::ctz(__pos.unmarked_values(60)) + 1;
    int v2 = tools::ctz(__pos.unmarked_values(61)) + 1;
    int v3 = tools::ctz(__pos.unmarked_values(62)) + 1;

    __pos.mark(60, v1);
    __pos.mark(61, v2);
    __pos.mark(62, v3);

    uint64_t res = square_63_cut(__pos);

    __pos.unmark(60, v1);
    __pos.unmark(61, v2);
    __pos.unmark(62, v3);

    return res;
        
}

inline uint64_t square_57_cut(sudoku_board& __pos)
{
    _Data_Type row6 = __pos.row(6);

    _Data_Type v1 = __pos.all() ^ (__pos.column(3) | row6);
    _Data_Type v2 = __pos.all() ^ (__pos.column(4) | row6);
    _Data_Type v3 = __pos.all() ^ (__pos.column(5) | row6);

    uint64_t res = 0;

    while (v1 != 0)
    {
        const int n1 = tools::next_idx(v1);
        __pos.mark(57, n1);

        _Data_Type lv2 = v2;
        while (lv2 != 0)
        {
            const int n2 = tools::next_idx(lv2);
            __pos.mark(58, n2);

            _Data_Type lv3 = v3;
            while (lv3 != 0)
            {
                const int n3 = tools::next_idx(lv3);
                __pos.mark(59, n3);
                res += square_60_cut(__pos);
                __pos.unmark(59, n3);
            }
            __pos.unmark(58, n2);
        }
        __pos.unmark(57, n1);
    }

    return res;
}

inline uint64_t __3count_recursion__(sudoku_board& __pos, uint64_t curr_square)
{
    if (curr_square == 72)
        return 1;
    
    if (curr_square == 57)
        return square_57_cut(__pos);

    uint64_t res = 0;

    _Data_Type v1 = __pos.unmarked_values(curr_square);
    while (v1 != 0)
    {
        const int n1 = tools::next_idx(v1);
        __pos.mark(curr_square, n1);

        _Data_Type v2 = __pos.unmarked_values(curr_square + 1);
        while (v2 != 0)
        {
            const int n2 = tools::next_idx(v2);
            __pos.mark(curr_square + 1, n2);

            _Data_Type v3 = __pos.unmarked_values(curr_square + 2);
            while (v3 != 0)
            {
                const int n3 = tools::next_idx(v3);
                __pos.mark(curr_square + 2, n3);
                res += __3count_recursion__(__pos, curr_square + 3);
                __pos.unmark(curr_square + 2, n3);
            }
            __pos.unmark(curr_square + 1, n2);
        }
        __pos.unmark(curr_square, n1);
    }

    return res;
}

}


uint64_t
__count_recursive__(sudoku_board& __pos,
    uint64_t curr_square, uint64_t end_square)
{
    if (curr_square == end_square) return 1;

    if (!__pos.empty(curr_square))
        return __count_recursive__(__pos, curr_square + 1, end_square);

    if (curr_square == 57)
        return search_optimisations::square_57_cut(__pos);

    _Data_Type left_values = __pos.unmarked_values(curr_square);
    uint64_t boards_found = 0;

    while (left_values != 0)
    {
        const int num = tools::next_idx(left_values);

        __pos.mark(curr_square, num);
        boards_found += __count_recursive__(__pos, curr_square + 1, end_square);
        __pos.unmark(curr_square, num);
    }

    return boards_found;
}

/**
 * @brief Counts the no. of legal sudoku boards that can be reached from current pos.
 * 
 * @param __pos Sudoku board position
 */
void
count(const std::string& __pos)
{
    tools::start_clock();

    sudoku_board board = __pos;
    const auto boards_found = sudoku::__count_recursive__(board, 0, 72ULL);

    const auto time_taken = tools::end_clock();

    std::cout << "Boards Found : " << boards_found << '\n';
    std::cout << "Speed : " << static_cast<double>(boards_found)
             / (time_taken * 1e6) << " M boards/sec.\n" << std::endl;
}


bool
__solve_recursive__(sudoku_board& __pos,
    uint64_t square_no = 0ULL)
{
    if (square_no == 81ULL) return true;

    if (__pos.empty(square_no) == false)
        return __solve_recursive__(__pos, square_no + 1);

    _Data_Type left_values = __pos.unmarked_values(square_no);

    while (left_values != 0)
    {
        const int num = tools::next_idx(left_values);

        __pos.mark(square_no, num);
        if (__solve_recursive__(__pos, square_no + 1)) return true;
        __pos.unmark(square_no, num);
    }

    return false;
}

/**
 * @brief Solves the sodoku position, return false is no solution is possible.
 * 
 * @param __pos Sudoku board position
 */
void
solve(const std::string& __pos)
{
    sudoku_board board = __pos;

    puts("Position : ");
    board.show();

    bool solution = __solve_recursive__(board);

    if (solution)
        puts("Board is valid!");

    puts("Solution : ");
    board.show();
}

/**
 * @brief Returns the state of board.\n
 * Returns 0, if current sudoku __pos has no solution.
 * Returns 1, if current sudoku __pos has 1 unique solution.
 * Returns 2, if current sudoku __pos has more than one solution.
 * 
 * @param __pos 
 * @param square_no 
 * @return int 
 */
int
solution_check(sudoku_board& __pos, uint64_t square_no = 0ULL)
{
    if (square_no == 81) return 1;

    if (__pos.empty(square_no) == false)
        return solution_check(__pos, square_no + 1);

    _Data_Type left_values = __pos.unmarked_values(square_no);
    int boards_found = 0;

    while (left_values != 0)
    {
        const int num = tools::next_idx(left_values);

        __pos.mark(square_no, num);
        boards_found += solution_check(__pos, square_no + 1);
        __pos.unmark(square_no, num);

        if (boards_found > 1) break;
    }

    boards_found = std::min(boards_found, 2);
    return boards_found;
}


namespace multi_thread
{

std::mutex thread_lock;

void
__generate_n_boards__(sudoku_board& __pos,
    std::vector<sudoku_board>& v, uint64_t curr_square, uint64_t end_square)
{
    if (curr_square == end_square)
    {
        v.emplace_back(__pos);
        return;
    }

    if (__pos.empty(curr_square) == false)
        return __generate_n_boards__(__pos, v, curr_square + 1, end_square);

    _Data_Type left_values = __pos.unmarked_values(curr_square);

    while (left_values != 0)
    {
        const int num = tools::next_idx(left_values);

        __pos.mark(curr_square, num);
        __generate_n_boards__(__pos, v, curr_square + 1, end_square);
        __pos.unmark(curr_square, num);
    }
}

std::vector<sudoku_board>
__generate_list__(sudoku_board& __pos, int threads_in_use)
{
    const uint64_t avg_boards_to_solve_per_thread = 1000;
    const uint64_t boards_to_solve = threads_in_use
                      * avg_boards_to_solve_per_thread;

    uint64_t end_sq = 0;

    for (end_sq = 1; end_sq < 81ULL; end_sq++)
    {
        uint64_t current = __count_recursive__(__pos, 0, end_sq);
        if (current >= boards_to_solve) break;
    }

    std::vector<sudoku_board> board_list;
    __generate_n_boards__(__pos, board_list, 0, end_sq);
    return board_list;
}


void
worker(std::vector<sudoku_board> pboards,
    uint64_t& index, uint64_t& global_boards_found)
{    
    uint64_t boards_found = 0;
    const uint64_t end_index = pboards.size();
    uint64_t solved = 0;

    while (true)
    {    
        thread_lock.lock();
        const bool valid_index = index < end_index;
        const uint64_t board_no = index++;
        thread_lock.unlock();

        if (!valid_index) break;

        boards_found += __count_recursive__(pboards[board_no], 0, 72);
        ++solved;
    }

    thread_lock.lock();
    global_boards_found += boards_found;
    thread_lock.unlock();
}

void
count(const std::string& __pos, const int threadCount)
{
    tools::start_clock();

    sudoku_board board_to_count = __pos;
    auto pboards = __generate_list__(board_to_count, threadCount);

    std::vector<std::thread> threads(threadCount);

    const auto __first = std::begin(threads);
    const auto __last  = std::end(threads);
    uint64_t current_index = 0;
    uint64_t boards_found = 0;

    for (auto current = __first; current != __last; ++current)
        *current = std::thread(worker, pboards,
                   std::ref(current_index), std::ref(boards_found));
    
    for (auto current = __first; current != __last; ++current)
        current->join();

    // std::vector<uint64_t> results(pboards.size());
    // std::transform(begin(pboards), end(pboards), begin(results), __count_rec__);
    // boards_found = std::accumulate(begin(results), end(results), boards_found);

    const auto time_taken = tools::end_clock();

    std::cout << "Boards Found : " << boards_found << '\n';
    std::cout << "Speed : " << static_cast<double>(boards_found)
             / (time_taken * 1e6) << " M boards/sec.\n" << std::endl;
}



}


}


void task(int argc, char **argv)
{

    if (argc < 3)
    {
        puts("Invalid Task!!\n");
        return;
    }

    std::string task = std::string(argv[1]);
    std::string __pos = std::string(argv[2]);

    if (task == "count")
        sudoku::multi_thread::count(__pos, 6);
    else if (task == "solve")
        sudoku::solve(__pos);
}


int main(int argc, char **argv)
{
    task(argc, argv);
    // std::cout << "Calls : " << function_calls << std::endl;

    // sudoku_board __pos = std::string("123456789");
    // // __pos.show();
    // tools::start_clock();
    // std::cout << sudoku::__count_recursive__(__pos, 0, 27) << std::endl;
    // std::cout << "Time : " << tools::end_clock() << " sec." << std::endl;
    // for (const auto& val : values)
    //     std::cout << val.first << " -> " << val.second << std::endl;

}


