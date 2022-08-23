#include <iostream>
#include <vector>


class BigInt {

    void trim (std::vector<int> &arr) {
        while (arr.back() == 0 && arr.size() > 1) arr.pop_back();
    }

    void plus_coroutine(const std::vector<int> &a, const std::vector<int> &b, std::vector<int> &ans) {
        int N = a.size(), M = b.size(), l = (N > M ? N : M);
        ans.resize(l + 2);
        
        for (int i = 0; i < ans.size() - 1; i++) {
            if (i < N) ans[i] += a[i];
            if (i < M) ans[i] += b[i];
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
        }

    }

    void minus_coroutine(const std::vector<int> &a, const std::vector<int> &b, std::vector<int> &ans) {
        const int M = b.size();
        ans = a;
        for (int i = 0; i < M; i++) {
            if (ans[i] >= b[i]) ans[i] -= b[i];
            else {
                ans[i] += 10 - b[i];
                int idx = i + 1;
                while (!ans[idx]) ans[idx++] = 9;
                ans[idx]--;
            }
        }
    }

    void multiply(std::vector<int> &arr, std::vector<int> &ans, long long num, int start) {
        const int N = arr.size();
        long long carry = 0;
        for (int i = 0; i < N; i++) {
            long long val = (arr[i] * num) + carry + ans[start];
            ans[start] = val % 10;
            carry = val / 10;
            start++;
        }

        while (carry) {
            long long val = carry + ans[start];
            ans[start] += val % 10;
            carry /= 10;
            start++;
        }
    }
    
    int is_greater(const std::vector<int> &a, const std::vector<int> &b) {
        const int N = a.size(), M = b.size();
        if (N > M) return 1;
        if (N < M) return -1;
        for (int i = N - 1; i >= 0; i--) {
            if (a[i] > b[i]) return 1;
            else if (a[i] < b[i]) return -1;
        }
        return 0;
    }

    long long binpow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }

    int __find_div(BigInt& a, BigInt &b, BigInt& res) {

        int div, N = a.len(), M = b.len(), x = 0, y = 0, w = 6;
        
        for (int i = N - 1, j = M - 1; i >= N - w; i--, j--) {
            x = 10 * x + a.digits[i];
            y = 10 * y + b.digits[j];
        }
        if (N > M) x = 10 * x + a.digits[N - w - 1];
        div = x / y;
        res = b * div;

        while (res > a) {
            res -= b;
            div--;
        }
        a -= res;
        return div;
    }

    int __find_div_fast(BigInt& a, BigInt& b, std::vector<BigInt> &res) {
        int div, N = a.len(), M = b.len(), x = 0, y = 0, w = 3;
        
        for (int i = N - 1, j = M - 1; i >= N - w; i--, j--) {
            x = 10 * x + a.digits[i];
            y = 10 * y + b.digits[j];
        }
        if (N > M) x = 10 * x + a.digits[N - w - 1];
        div = x / y;
        if (div >= 10) div = 9;
        while (res[div] > a) div--;
        a -= res[div];
        return div;
    }

    public:

    int sign = 1;
    std::vector <int> digits;

    BigInt() {
        digits.emplace_back(0);
        sign = 1;
    }

    int __sign() {
        return sign;
    }

    int len() { // O(1)
        return digits.size();
    }

    int digitAt(int idx) {  // O(1)
        return digits[idx];
    }

    int sum_of_digits() {
        int res = 0;
        for (int i : digits) res += i;
        return res;
    }

    //////     +      //////

    BigInt operator + (const BigInt& num);

    void operator += (const BigInt& num);

    void operator ++ (int tmp);

    void operator += (long long num);

    //////     -      //////

    BigInt operator - (const BigInt& num);
    
    void operator -= (const BigInt& num);

    //////     *      //////

    BigInt operator * (const BigInt& num);

    BigInt operator * (const long long num);

    void operator *= (const BigInt& num);

    void operator *= (const long long num);

    //////     '/'      //////

    BigInt operator / (BigInt b);

    BigInt operator % (BigInt& b);

    long long operator % (const long long m);

    BigInt operator / (long long num);

    //////     Bitwise Op.      //////

    void operator <<= (const int shift);

    BigInt operator << (const int shift);

    BigInt operator >> (const int shift);

    //////     comparaters      //////

    bool operator < (const BigInt& num);
    
    bool operator <= (const BigInt& num);

    bool operator > (const BigInt& num);

    bool operator >= (const BigInt& num);
    
    bool operator == (const BigInt &num);

    bool operator != (const BigInt &num);

    //////     read/write      //////

    void r();

    std::string str();

    void operator = (const std::string str);
    
    void operator = (long long num);

    std::string bin();

};


#pragma region BigInt Functions


#pragma region Utility

BigInt multiply_by_ten(BigInt&a, int _power_of_ten) {
    BigInt ans;
    ans.sign = a.sign;
    ans.digits.clear();
    for (int i = 0; i < _power_of_ten; i++) ans.digits.emplace_back(0);
    for (int i = 0; i < a.digits.size(); i++) ans.digits.emplace_back(a.digits[i]);
    return ans;
}

BigInt starting_N_digits(BigInt &a, int N) {
    BigInt ans;
    ans.digits.clear();
    ans.sign = a.sign;
    for (int i = N; i < a.digits.size(); i++) ans.digits.emplace_back(a.digits[i]);
    return ans;
}

BigInt ending_N_digits(BigInt& a, int N) {
    BigInt ans;
    ans.digits.clear();
    for (int i = 0; i < N; i++) {
        ans.digits.emplace_back(a.digits[i]);
    }
    return ans;
}

std::string big_rand(int __lower = 1, int __upper= 30) {
    std::string res;
    int _x = __lower + (rand() * rand()) % (__upper - __lower + 1), num;
    num = 1 + rand() % 9;
    res.push_back((1 + rand() % 9) + '0');
    for (int i = 1; i < _x; i++) res.push_back((rand() % 9) + '0');
    return res;
}

BigInt bigpow(BigInt a, BigInt b) {   // O(d * d * d)
    BigInt ans;
    ans = 1;
    while (true) {  // O(log(b)) -> O(d)
        if (b.len() == 1 && !b.digitAt(0)) break;
        if (b.digitAt(0) % 2) ans *= a; // O(d * d)
        b = b >> 1; // O(d)
        a *= a; // O(d * d)
    }
    return ans;
}

BigInt bigpow(BigInt a, long long b) {  // O(d * d * log(b))
    BigInt ans;
    ans = 1;
    while (b) {     // log(b)
        if (b & 1) ans *= a;    // O(d * d)
        b >>= 1;
        a *= a;     //  O(d * d)
    }
    return ans;
}

BigInt bigpow(long long __n, long long b) {
    BigInt ans, a;
    ans = 1; a = __n;
    while (b) {  // O(log(b)) -> O(d)
        if (b & 1) ans *= a;    // O(d * d)
        b >>= 1;
        a *= a; // O(d * d)
    }
    return ans;
}

long long ToLong(BigInt& a) {
    long long res = 0;
    for (int i = a.len() - 1; i >= 0; i--)
        res = (10 * res) + a.digitAt(i);
    if (a.__sign() == -1) res *= -1;
    return res;
}

#pragma endregion


#pragma region Read/Write

void BigInt::operator = (const std::string s) { // O(d)
    try {
        const int N = s.length();
        if (N == 1 && s[0] == '-') throw "Not a Valid Number!";
        if ((s[0] > '9' || s[0] < '0') && s[0] != '-') throw "Not a Valid Number!";
        for (int i = 1; i < N; i++) {
            if (s[i] > '9' || s[i] < '0') throw "Not a Valid Number!";
        }
        sign = 1;
        digits.clear();
        int i = 0;
        if (s[i] == '-') {
            sign = -1;
            i++;
        }
        for (; i < N; i++) digits.emplace_back(s[i] - '0');
        const int M = digits.size();
        for (int i = 0; i < M / 2; i++) {
            int tmp = digits[i];
            digits[i] = digits[M - 1 - i];
            digits[M - 1 - i] = tmp;
        }
        trim(digits);
        if (digits.size() == 1 && !digits[0]) sign = 1;
    }
    catch(const char* msg) {
        std::cout << msg << std::endl;
    }
}

void BigInt::operator = (long long num) { // O(d)
    digits.clear();
    if (!num) digits.emplace_back(0);
    if (num < 0) sign = -1;
    while (num) {
        digits.emplace_back(num % 10);
        num /= 10;
    }
}

void BigInt::r() {
    std::string s; std::cin >> s;

    try {
        const int N = s.length();
        if (N == 1 && s[0] == '-') throw "Not a Valid Number!";
        if ((s[0] > '9' || s[0] < '0') && s[0] != '-') throw "Not a Valid Number!";
        for (int i = 1; i < N; i++) {
            if (s[i] > '9' || s[i] < '0') throw "Not a Valid Number!";
        }
        int i = 0; sign = 1; digits.clear();
        if (s[i] == '-') {
            sign = -1;
            i++;
        }
        for (; i < N; i++) digits.emplace_back(s[i] - '0');
        const int M = digits.size();
        for (int i = 0; i < M / 2; i++) {
            int tmp = digits[i];
            digits[i] = digits[M - 1 - i];
            digits[M - 1 - i] = tmp;
        }
        trim(digits);
        if (digits.size() == 1 && !digits[0]) sign = 1;
    }
    catch(const char* msg) {
        std::cout << msg << std::endl;
    }

    return;
}

std::string BigInt::str() {
    std::string ans;
    if (sign == -1) ans.push_back('-');
    for (int i = digits.size() - 1; i >= 0; i--) {
        ans.push_back(digits[i] + '0');
    }
    return ans;
}

std::string BigInt::bin() { // O(d * d)

    // Not supported for negative integers
    BigInt num;
    num.sign = sign;
    num.digits = digits;
    std::string ans;
    
    while (true) {      //  O(d)
        if (num.digits.size() == 1 && !num.digitAt(0)) break;
        ans.push_back((num.digitAt(0) & 1) + '0');
        num = num >> 1;     // O(d)
    }
    const int N = ans.size();
    for (int i = 0; i < N / 2; i++) {
        char tmp = ans[i];
        ans[i] = ans[N - 1 - i];
        ans[N - 1 - i] = tmp;
    }
    return ans;
}


#pragma endregion


#pragma region plus

BigInt BigInt::operator + (const BigInt& num) { // O(d)
    BigInt ans;

    int task = sign * num.sign;
    if (task == 1) {
        ans.sign = sign;
        plus_coroutine(digits, num.digits, ans.digits);
        trim(ans.digits);
        return ans;
    }
    int a_first = is_greater(digits, num.digits);
    if (a_first == 0) return ans;   /// Return 0 if a == b
    if (a_first == 1) {
        ans.sign = sign;
        minus_coroutine(digits, num.digits, ans.digits);
        trim(ans.digits);
        return ans;
    }
    ans.sign = num.sign;
    minus_coroutine(num.digits, digits, ans.digits);
    trim(ans.digits);
    return ans;

}

void BigInt::operator += (const BigInt& num) { // O(d)
    int N = digits.size(), M = num.digits.size();
    if (M > N) digits.resize(M);
    int carry = 0;
    for (int i = 0; i < M; i++) {
        int val = digits[i] + num.digits[i] + carry;
        digits[i] = val % 10;
        carry = val / 10;
    }
    for (int i = M; i < N; i++) {
        int val = digits[i] + carry;
        digits[i] = val % 10;
        carry = val / 10;
    }

    if (carry) digits.emplace_back(carry);
}

void BigInt::operator += (long long carry) {
    // Only for positive integers
    int cnt = 0, N = digits.size();
    while (carry && cnt < N) {
        long long tmp = digits[cnt] + carry;
        carry = tmp / 10;
        digits[cnt] = tmp % 10;
        cnt++;
    }
    while (carry) {
        digits.emplace_back(carry % 10);
        carry /= 10;
    }
}

void BigInt::operator ++ (int tmp) { // O(1)
    digits[0]++;
    if (digits[0] != 10) return;
    digits[0] = 0;
    for (int i = 1; i < digits.size(); i++) {
        digits[i]++;
        if (digits[i] != 10) return;
        digits[i] = 0;
    }
    digits.emplace_back(1);
}

#pragma endregion


#pragma region minus

BigInt BigInt::operator - (const BigInt& num) {
    BigInt ans;
    int task = sign * num.sign * -1;

    if (task == 1) {
        ans.sign = sign;
        plus_coroutine(digits, num.digits, ans.digits);
        return ans;
    }
    
    int a_first = is_greater(digits, num.digits);

    if (a_first == 0) return ans;
    if (a_first == 1) {
        ans.sign = sign;
        minus_coroutine(digits, num.digits, ans.digits);
        trim(ans.digits);
        return ans;
    }
    ans.sign = num.sign * -1;
    minus_coroutine(num.digits, digits, ans.digits);
    trim(ans.digits);
    return ans;
}

void BigInt::operator -= (const BigInt& b) {

    // This assumes number b is smaller than this number.

    const int M = b.digits.size();
    for (int i = 0; i < M; i++) {
        if (digits[i] >= b.digits[i]) digits[i] -= b.digits[i];
        else {
            digits[i] += + 10 - b.digits[i];
            int idx = i + 1;
            while (!digits[idx]) digits[idx++] = 9;
            digits[idx]--;
        }
    }

    trim(digits);

}


#pragma endregion


#pragma region multiply

BigInt BigInt::operator * (const BigInt& num) { // O((d * d) / 16)
    BigInt ans;
    ans.sign = sign * num.sign;
    int N = digits.size(), M = num.digits.size();
    ans.digits.resize(N + M);
    int num_size = 16;
    for (int i = 0; i < M; i += num_size) {
        long long val = 0;
        int s = (i + num_size < M ? i + num_size : M);
        for (int j = s - 1; j >= i; j--) val = 10 * val + num.digits[j];
        multiply(digits, ans.digits, val, i);
    }
    trim(ans.digits);
    if (ans.digits.size() == 1 && !ans.digits[0]) ans.sign = 1;
    return ans;
}

void BigInt::operator *= (const BigInt& num) {
    BigInt ans;
    ans.sign = sign * num.sign;
    int N = digits.size(), M = num.digits.size();
    ans.digits.resize(N + M);
    int num_size = 16;
    for (int i = 0; i < M; i += num_size) {
        long long val = 0;
        int s = (i + num_size < M ? i + num_size : M);
        for (int j = s - 1; j >= i; j--) val = 10 * val + num.digits[j];
        multiply(digits, ans.digits, val, i);
    }
    trim(ans.digits);
    if (ans.digits.size() == 1 && !ans.digits[0]) ans.sign = 1;
    sign = ans.sign;
    digits = ans.digits;
    return;
}

BigInt BigInt::operator * (const long long num) { // O(d)
    long long carry = 0;
    int N = digits.size();
    BigInt ans;
    ans.digits.resize(N);
    for (int i = 0; i < N; i++) {
        long long val = digits[i] * num + carry;
        ans.digits[i] = val % 10;
        carry = val / 10;
    }
    while (carry) {
        ans.digits.emplace_back(carry % 10);
        carry /= 10;
    }

    if (ans.digits.size() == 1 && !ans.digits[0]) ans.sign = 1;
    return ans;
}

void BigInt::operator *= (const long long num) { // O(d)
    long long carry = 0;
    int N = digits.size();
    if (num < 0) sign *= -1;
    for (int i = 0; i < N; i++) {
        long long val = digits[i] * num + carry;
        digits[i] = val % 10;
        carry = val / 10;
    }
    while (carry) {
        digits.emplace_back(carry % 10);
        carry /= 10;
    }
    if (digits.size() == 1 && !digits[0]) sign = 1;
    return;
}

#pragma endregion


#pragma region div/mod

long long BigInt::operator % (const long long m) { // O(d)
    long long num = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        num = 10 * num + digits[i];
        if (num >= m) num %= m;
    }
    return num;
}

BigInt BigInt::operator % (BigInt& b) {
    BigInt ans, a;
    // To Be Done
    if (b.digits.size() == 1 && !b.digits[0]) {     // Division by 0 check
        std::cout << "Divide by Zero Error!" << std::endl;
        return ans;
    }
    // If b < 10 ^ 16 -> Just Convert To Int and Return Modulo , O(d)
    if (b.len() < 12) {
        a.digits = digits; a.sign = sign;
        long long _x = a % ToLong(b);
        ans = _x;
        return ans;
    }

    a.digits = digits; a.sign = sign;
    if (b.digits.size() > digits.size()) return a;

    a.digits.clear();
    int N = digits.size(), cnt = N - 1;

    std::vector<BigInt> result(10);
    for (int i = 1; i < 10; i++) result[i] = b * i;
    while (cnt >= 0) {
        while (a < b && cnt >= 0) {
            a *= 10;
            a += digits[cnt--];
        }
        if (a < b) break;
        int div = __find_div_fast(a, b, result);
    }
    trim(a.digits);
    return a;
}

BigInt BigInt::operator / (long long num) {     // O(d)
    BigInt ans;
    if (num == 0) {
        std::cout << "Division by Zero Error!" << std::endl;
        return ans;
    }
    ans.sign = sign;
    if (num < 0) {
        ans.sign *= -1;
        num *= -1;
    }
    
    int N = digits.size(), cnt = N - 2;
    long long val = digits[N - 1];

    if (val >= num) {
        ans.digits.emplace_back(val / num);
        val %= num;
    }

    while (cnt >= 0) {
        val = 10 * val + digits[cnt];
        ans.digits.emplace_back(0);
        if (val >= num) {
            ans.digits[ans.digits.size() - 1] = val / num;
            val %= num;
        }
        cnt--;
    }
    
    N = ans.digits.size();
    for (int i = 0; i < N / 2; i++) {
        int tmp = ans.digits[i];
        ans.digits[i] = ans.digits[N - 1 - i];
        ans.digits[N - 1 - i] = tmp;
    }
    trim(ans.digits);

    return ans;
}

BigInt BigInt::operator / (BigInt b) {
    BigInt ans, a, tmp;
    if (b.digits.size() == 1 && !b.digits[0]) {     // Division by 0 check
        std::cout << "Divide by Zero Error!" << std::endl;
        return ans;
    }
    
    // If b < 10 ^ 16 -> Just Convert To Int and Divide , O(d)
    if (b.len() < 16) {
        a.digits = digits; a.sign = sign;
        return a / ToLong(b);
    }
    
    if (b.digits.size() > digits.size()) return ans;    // If dividend less than divisor, return 0
    
    a.digits.clear();
    int N = digits.size(), cnt = N - 1;

    std::vector<BigInt> result(10, b);
    for (int i = 2; i < 10; i++) result[i] += result[i - 1];
    while (cnt >= 0) {
        while (a < b && cnt >= 0) {
            a *= 10;
            a += digits[cnt--];
            ans.digits.emplace_back(0);
        }
        if (a < b) break;
        int div = __find_div_fast(a, b, result);
        ans.digits[ans.digits.size() - 1] = div;
    }
    // Reversing the digits in answer
    N = ans.digits.size();
    for (int i = 0; i < N / 2; i++) {
        std::swap(ans.digits[i], ans.digits[N - 1 - i]);
        // int tmp = ans.digits[i];
        // ans.digits[i] = ans.digits[N - 1 - i];
        // ans.digits[N - 1 - i] = tmp;
    }
    trim(ans.digits);

    return ans;
}

#pragma endregion


#pragma region Comparators

bool BigInt::operator < (const BigInt& num) { // O(d)
    const int N = digits.size(), M = num.digits.size();
    if (N < M) return true;
    if (N > M) return false;
    for (int i = N - 1; i >= 0; i--) {
        if (digits[i] < num.digits[i]) return true;
        else if (digits[i] > num.digits[i]) return false;
    }
    return false;
}

bool BigInt::operator <= (const BigInt& num) { // O(d)
    const int N = digits.size(), M = num.digits.size();
    if (N < M) return true;
    if (N > M) return false;
    for (int i = N - 1; i >= 0; i--) {
        if (digits[i] < num.digits[i]) return true;
        else if (digits[i] > num.digits[i]) return false;
    }
    return true;
}

bool BigInt::operator > (const BigInt& num) { // O(d)
    const int N = digits.size(), M = num.digits.size();
    if (N > M) return true;
    if (N < M) return false;
    for (int i = N - 1; i >= 0; i--) {
        if (digits[i] > num.digits[i]) return true;
        else if (digits[i] < num.digits[i]) return false;
    }
    return false;
} 

bool BigInt::operator >= (const BigInt& num) { // O(d)
    const int N = digits.size(), M = num.digits.size();
    if (N > M) return true;
    if (N < M) return false;
    for (int i = N - 1; i >= 0; i--) {
        if (digits[i] > num.digits[i]) return true;
        else if (digits[i] < num.digits[i]) return false;
    }
    return true;
}

bool BigInt::operator == (const BigInt &num) { // O(d)
    if (sign != num.sign) return false;
    const int N = digits.size(), M = num.digits.size();
    if (N != M) return false;
    for (int i = 0; i < N; i++) {
        if (digits[i] != num.digits[i]) return false;
    }
    return true;
}

bool BigInt::operator != (const BigInt &num) { // O(d)
    if (sign != num.sign) return true;
    const int N = digits.size();
    if (N != num.digits.size()) return true;
    for (int i = 0; i < N; i++) if (digits[i] != num.digits[i]) return true;
    return false;
}

#pragma endregion


#pragma region Bitwise

void BigInt::operator <<= (const int shift) {
    if (shift < 0) {
        std::cout << "Negative Shift Error!" << std::endl;
        return;
    }
    long long num = (long long)1 << shift, carry = 0;
    const int N = digits.size();
    for (int i = 0; i < N; i++) {
        long long val = digits[i] * num + carry;
        digits[i] = val % 10;
        carry = val / 10;
    }
    while (carry) {
        digits.emplace_back(carry % 10);
        carry /= 10;
    }
    if (digits.size() == 1 && !digits[0]) sign = 1;
    return;
}

BigInt BigInt::operator << (const int shift) {

    // Shift should be less than or equal to 56
    BigInt ans;
    try {
        if (shift > 56) throw "Shift greater than 56 Error!";
        if (shift < 0) throw "Negative Shift Error!";
        long long carry = 0, num = 1LL << shift;
        int N = digits.size(), cnt = 0;
        ans.digits.resize(N + 20);
        ans.digits.pop_back();
        for (int i = 0; i < N; i++) {
            long long val = digits[i] * num + carry;
            ans.digits[cnt++] = val % 10;
            carry = val / 10;
        }

        while (carry) {
            ans.digits[cnt++] = carry % 10;
            carry /= 10;
        }
        trim(ans.digits);
        if (ans.digits.size() == 1 && !ans.digits[0]) ans.sign = 1;
        return ans;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    return ans;
    
}

BigInt BigInt::operator >> (const int shift) {

    int N = digits.size(), cnt;
    BigInt ans;
    if (shift < 0) {
        std::cout << "Negative Shift Error!" << std::endl;
        return ans;
    }
    ans.digits.resize(N);
    long long carry = 0, mul = binpow(5, shift);


    for (cnt = 0; cnt < shift; cnt++) {
        long long val = digits[cnt] * mul + carry;
        carry = val / 10;
    }

    for (; cnt < N; cnt++) {
        long long val = digits[cnt] * mul + carry;
        if (cnt >= shift) ans.digits[cnt - shift] = val % 10;
        carry = val / 10;
    }

    cnt -= shift;

    while (carry) {
        if (cnt >= 0) ans.digits[cnt] = carry % 10;
        carry /= 10;
        cnt++;
    }

    trim(ans.digits);
    return ans;
}

#pragma endregion

#pragma endregion

