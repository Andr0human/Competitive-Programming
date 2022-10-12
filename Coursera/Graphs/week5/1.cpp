#include <bits/stdc++.h>
#include "../../../lib/union_table.h"
using namespace std;

int
square(int x)
{ return x * x; }

class edge
{
public:
    int from, to;
    double cost;

    edge()
    : from(0), to(0) {}

    edge(int _from, int _to, double _cost)
    : from(_from), to(_to), cost(_cost) {}
};


void print(vector<edge> & list)
{
    for (auto edge : list)
    {
        cout << "From : " << edge.from << " | To : " << edge.to;
        cout << " | Cost : " << edge.cost << endl;
    }
}

vector<edge>
get_graph(int n)
{
    vector<edge> list;
    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            auto p = points[i], q = points[j];
            int cost = square(abs(p.first - q.first)) + square(abs(p.second - q.second));
            list.emplace_back(edge(i, j, cost));
        }
    }

    return list;
}

vector<edge>
kruskal(int n, vector<edge> &edge_list)
{
    union_table u(n);
    vector<edge> res;

    for (auto e : edge_list)
    {
        if (u.is_connected(e.from, e.to))
            continue;
        u.unify(e.from, e.to);
        res.emplace_back(e);
    }
    return res;
}

double
final_cost(vector<edge> list)
{
    double res = 0;
    for (auto e : list)
        res += sqrt(e.cost);
    return res;
}

int main()
{    
    int n; cin >> n;
    auto edge_list = get_graph(n);
    auto cmp = [] (edge a, edge b)
    { return a.cost < b.cost; };

    sort(edge_list.begin(), edge_list.end(), cmp);
    // print(edge_list);

    auto res = kruskal(n, edge_list);
    // cout << "Printing res = \n";
    // print(res);
    cout << setprecision(10) << final_cost(res) << endl;
}


/*

0 0 - 0
0 2 - 1
1 1 - 2
3 0 - 3
3 2 - 4


*/
