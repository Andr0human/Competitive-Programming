
#include <vector>
#include <string>

using std::vector;
using std::string;

static vector<int>
computeLPS(string &pat) {
    const size_t m = pat.length();
    size_t i = 1;
    int len = 0;
    vector<int> res(m);
    res[0] = 0;
    
    while (i < m) {
        if (pat[i] == pat[len]) res[i++] = ++len;
        else {
            if (len) len = res[len - 1];
            else res[i++] = 0;
        }
    }
    return res;
}

int kmp_search(string &text, string &pat) {
    
    const size_t n = text.length();
    const size_t m = pat.length();
    
    auto lps = computeLPS(pat);
    
    size_t i = 0, j = 0;
    int res = 0;
    
    while (i < n) {
        if (text[i] == pat[j]) {
            i++;
            j++;
        }
        else {
            if (j) j = lps[j - 1];
            else i++;
        }
        if (j == m) {
            res++;
            j = lps[j - 1];
        }
    }
    return res;
}


