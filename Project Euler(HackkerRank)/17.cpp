/***
 * Project Euler #17: Number to Words
 * Approach : Make a list of words of basic nums and then brute force it.
***/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
map<int, string> nums;
const ll billion = (ll)1e9;
const ll million = (ll)1e6;
const ll trillion = (ll)1e12;

string InHundreds(ll val) {
    string res = "";
    int a0 = val / 100, a1 = (val / 10) % 10, a2 = val % 10;

    if (nums.find(val) != nums.end()) {
        if (a0 == 1) res += nums[1] + " ";
        res += nums[val] + " ";
        return res;
    }
    if (a0) {
        res += nums[a0] + " " + nums[100] + " ";
    }
    if (a1 * 10 + a2 <= 20) {
        res += nums[a1 * 10 + a2] + " ";
    } else {
        res += nums[a1 * 10] + " ";
        if (a2) res += nums[a2] + " ";
    }
    return res;
}

void ToWords(ll N) {
    if (N == 0) {
        cout << "Zero" << endl;
        return;
    }
    if (N == trillion) {
        cout << "One Trillion" << endl;
        return;
    }
    string answer = "";

    if (N >= billion) {
        answer += InHundreds(N / billion) + "Billion ";
    }
    N %= billion;
    if (N >= million) {
        answer += InHundreds(N / million) + "Million ";
    }
    N %= million;
    if (N >= 1000) {
        answer += InHundreds(N / 1000) + "Thousand ";
    }
    N %= 1000;
    if (N) answer += InHundreds(N);
    if (answer.back() == ' ') answer.pop_back();
    cout << answer << endl;
}

void build_basic_nums() {
    nums[1] = "One";        nums[2] = "Two";       nums[3]  = "Three";
    nums[4]  = "Four";      nums[5] = "Five";      nums[6]  = "Six";
    nums[7]  = "Seven";     nums[8]  = "Eight";    nums[9]  = "Nine"; 
    nums[10] = "Ten";       nums[12] = "Twelve";   nums[13] = "Thirteen";
    nums[14] = "Fourteen";  nums[15] = "Fifteen";  nums[16] = "Sixteen";
    nums[17] = "Seventeen"; nums[18] = "Eighteen"; nums[19] = "Nineteen";
    nums[20] = "Twenty";    nums[30] = "Thirty";   nums[40]  = "Forty";
    nums[50] = "Fifty";     nums[60] = "Sixty";    nums[70]  = "Seventy";
    nums[80] = "Eighty";    nums[90] = "Ninety";   nums[100] = "Hundred";
    nums[11] = "Eleven";
    return;
}


int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    build_basic_nums();

    int t; cin >> t;
    while (t--) {
        long long N;
        cin >> N;
        ToWords(N);
    }

}
