
#include "../../../lib/union_table.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


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

void
print(vector<edge> &list)
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

    auto cmp = [](pair<int, int> a, pair<int, int> b)
    {
        if (a.first < b.first) return true;
        if (a.first > b.first) return false;
        return a.second > b.second;
    };

    sort(points.begin(), points.end(), cmp);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int dist_x = points[i].first - points[j].first;
            int dist_y = points[i].second - points[j].second;

            double cost = sqrt(dist_x * dist_x + dist_y * dist_y);
            list.emplace_back(edge(i, j, cost));
        }
    }

    return list;
}

double
cluster(int n, int K, vector<edge> &edge_list)
{
    union_table u(n);
    double answer = edge_list.back().cost;

    for (auto e : edge_list)
    {
        if (!u.is_connected(e.from, e.to))
            u.unify(e.from, e.to);
        if (u.component_size() <= K)
            break;
    }

    for (auto e : edge_list)
        if (!u.is_connected(e.from, e.to))
            answer = min(answer, e.cost);

    return answer;
}

int main()
{
    int n, K;
    cin >> n;

    auto edge_list = get_graph(n);
    cin >> K;

    auto cmp = [](edge a, edge b) { return a.cost < b.cost; };
    sort(edge_list.begin(), edge_list.end(), cmp);
    // print(edge_list);

    auto res = cluster(n, K, edge_list);
    cout << setprecision(10) << res << endl;
}

