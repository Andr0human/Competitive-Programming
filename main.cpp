#include "kmp.h"
#include "lib/perf.h"
#include <bits/stdc++.h>

using namespace std;


struct dna_gene {
    string name;
    uint64_t health;
};


uint64_t compute_health(string &text, vector<dna_gene> &genes, int s, int e) {
    uint64_t res = 0;
    int current;
    for (int i = s; i <= e; i++) {

        current = kmp_search(text, genes[i].name);
        res += current * genes[i].health;
    }
    return res;
}


void solve(vector<dna_gene>& genes)
{
    perf::Timer _("Gene Compute");

    int t, s, e;
    cin >> t;

    string text;
    uint64_t best_max = 0, best_min = LLONG_MAX;
    uint64_t res;

    while (t--)
    {
        cin >> s >> e >> text;

        res = compute_health(text, genes, s, e);
        best_max = max(res, best_max);
        best_min = min(res, best_min);
    }

    cout << best_min << " " << best_max << endl;
}

int main()
{
    freopen("in", "r", stdin);

    int n;
    cin >> n;

    vector<dna_gene> genes(n);

    for (auto& gene : genes)
        cin >> gene.name;
    for (auto& gene : genes)
        cin >> gene.health;

    solve(genes);
}


