/**
 * @file templates.h
 * @author Ayush Sinha
 * @brief Standard template file for coding competitions.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __TEMPLATES__

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define all(x) begin(x), end(x)

string input() {
    string text;
    getline(cin, text);
    return text;
}
template<typename _Tp = int> _Tp
next() {
    _Tp value;
    cin >> value;
    return value;
}
template <typename _T1, typename _T2> pair<_T1, _T2>
next() {
    auto first = next<_T1>();
    auto second = next<_T2>();
    return make_pair(first, second);
}
template <typename _Sequence> _Sequence
next(size_t _Nm) {
    _Sequence c(_Nm);
    for (auto& value : c) cin >> value;
    return c;
}

template<typename _Tp> void
print (const _Tp& value, const string end = "") {
    cout << value << end;
}
template<typename _Tp1, typename _Tp2> void
print (const pair<_Tp1, _Tp2>& value, const string end = "") {
    cout << value.first << ' ' 
         << value.second << end;
}
template<typename _Tp> void
print (const vector<_Tp>& list, const string end = "\n", const string sep = " ") {

    if (list.empty())
        return print(end);

    auto __first = std::begin(list);
    auto __last  = std::end(list) - 1;

    for (; __first != __last; ++__first)
        print(*__first, sep);

    print(*__first, end);
}
template<typename _Tp> void
print (const vector<vector<_Tp>>& list, const string end = "\n", const string sep = "\n") {

    if (list.empty())
        return print(end);

    auto __first = std::begin(list);
    auto __last  = std::end(list) - 1;

    for (; __first != __last; ++__first)
        print(*__first, " ", sep);

    print(*__first, " ", end);
}
template<typename _Tp1, typename _Tp2> void
print (const map<_Tp1, _Tp2>& list, const string end = "\n", const string sep = "\n") {

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


