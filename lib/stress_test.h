
/**
 * @file stress_test.h
 * @author Ayush Sinha (https://github.com/Andr0human)
 * @brief
 * stress_test lib is used to compare results
 * of two functions on same input parameters.
 * 
 * It lists testcases on which two functions
 * are returning different values.
 * Refer to sample-code for how to use.
 * 
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __STRESS_TEST_H__
#define __STRESS_TEST_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <type_traits>

using std::string;
using std::pair;
using std::tuple;
using std::vector;

#ifndef __TEMPLATES_H__

#ifndef __PRINT_FUNCTIONS__

// print templates to print standard data_types

template<typename _Tp>
void
print (const _Tp& value, const string end = "")
{ std::cout << value << end; }

template<typename _Tp1, typename _Tp2>
void
print(const pair<_Tp1, _Tp2>& value, const string end = "")
{
    std::cout << value.first << ' ' 
         << value.second << end;
}

template<typename _Tp>
void
print (const vector<_Tp>& list, const string end = "\n", const string sep = " ")
{
    if (list.empty())
        return print(end);

    auto __first = std::begin(list);
    auto __last  = std::end(list) - 1;

    for (; __first != __last; ++__first)
        print(*__first, sep);

    print(*__first, end);
}
template<typename _Tp>
void
print(const vector<vector<_Tp>>& list, const string end = "\n", const string sep = "\n")
{
    if (list.empty())
        return print(end);

    auto __first = std::begin(list);
    auto __last  = std::end(list) - 1;

    for (; __first != __last; ++__first)
        print(*__first, sep, " ");

    print(*__first, end, " ");
}

template<typename _Tp1, typename _Tp2>
void
print(const std::map<_Tp1, _Tp2>& list, const string end = "\n", const string sep = "\n")
{
    if (list.empty())
        return print(end);

    auto __first = std::begin(list);
    auto __last  = std::end(list);

    --__last;

    for (; __first != __last; ++__first)
        print(*__first, sep);

    print(*__first, end);
}

#endif

#endif

#ifndef __PRINT_TUPLE__

// printTuple function to print tuples.
// https://www.geeksforgeeks.org/how-to-iterate-over-the-elements-of-an-stdtuple-in-c

template <size_t I = 0, typename... Ts>
typename std::enable_if<I == sizeof...(Ts), void>::type
printTuple(tuple<Ts...>)
{
    // If iterated through all values
    // of tuple, then simply return.
    return;
}

template <size_t I = 0, typename... _Types>
typename std::enable_if<(I < sizeof...(_Types)), void>::type
printTuple(tuple<_Types...> tup)
{
    // Print element of tuple
    print(std::get<I>(tup), "\n");
 
    // Go to next element
    printTuple<I + 1>(tup);
}

#endif


void
stress_test(const auto& __f1, const auto& __f2,
            const auto& params_gen,
            size_t testcases = 10'000,
            size_t max_failed_cases = 5)
{
    // Declare a vector of type (return_type of param_gen, unsigned long)
    // Used to store parameters of functions and testcase_index
    std::vector<pair<__typeof__(params_gen()), size_t>>
        failed_cases;

    for (size_t tc = 1; tc <= testcases; tc++)
    {
        // Generate parameters for functions using
        // user-provided parameter_generator function.
        const auto params = params_gen();

        // Stores the result of both functions for the generated params.
        const auto res1 = std::apply(__f1, params);
        const auto res2 = std::apply(__f2, params);

        if (res1 != res2)
        {
            /**
             * If results of f1 and f2 differs,
             * Store the parameters provided to the functions,
             * and testcase index.
            **/
            failed_cases.emplace_back(make_pair(params, tc));

            // break if collected enough failed_cases.
            if (failed_cases.size() >= max_failed_cases)
                break;
        }
    }

    using std::cout;

    // if (sort_cases)
    //     std::sort(begin(failed_cases), end(failed_cases));

    for (const auto& [failed_case_params, index] : failed_cases)
    {
        /**
         * @brief PrintOrder
         * TestCase Index
         * Result of __f1
         * Result of __f2
         * Params for __f1 and __f2
        **/

        cout << "Testcase " << index << '\n';
        cout << "Params : \n";
        // Print the tuple containing parameters
        printTuple(failed_case_params);

        cout << "\nRes1 = ";
        print(std::apply(__f1, failed_case_params));
        cout << "\nRes2 = ";
        print(std::apply(__f2, failed_case_params));

        // Leave an extra line after printing each failed_case
        cout << std::endl << std::endl;
    }
}


#endif

/***

            Sample-Test
 
int sum_of_vector1(int n, vector<int> arr)
{
    int res = 0;
    for (auto value : arr)
        res += value;
    return res;
}

int sum_of_vector2(int n, vector<int> arr)
{
    int res = 0;
    for (auto value : arr)
        res += value;
    
    if (n % 3 == 0)
        res += 10;
    return res;
}

auto
parameter_generator()
{
    int n = 1 + rand() % 20;

    vector<int> arr(n);
    for (auto& value : arr)
        value = 20 + rand() % 10;

    // Return all parameters in a tuple, (in same order
    // as to be taken by test functions.
    return std::tuple(n, arr);
}

stress_test(sum_of_vector1,
            sum_of_vector2,
            parameter_generator,
            1000, 3, true);

==>

Testcase 4
Res1 = 137
Res2 = 147
6
21 27 21 21 25 22

Testcase 25
Res1 = 216
Res2 = 226
9
26 21 22 24 22 25 28 26 22

Testcase 20
Res1 = 294
Res2 = 304
12
26 24 20 26 21 28 29 28 24 21 24 23

***/
