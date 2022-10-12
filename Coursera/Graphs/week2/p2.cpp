#include <bits/stdc++.h>
using namespace std;

#define INT_MATRIX std::vector<std::vector<int>>

vector<int> answer;
vector<bool> visited;

void
explore(INT_MATRIX &arr, int vertex)
{    
    if (visited[vertex]) return;

    for (int edge : arr[vertex])
    {
        if (!visited[edge])
            explore(arr, edge);
    }
    
    answer.emplace_back(vertex);
    visited[vertex] = true;
}

void
topo_sort(INT_MATRIX &arr)
{
    for (size_t i = 1; i < arr.size(); i++)
        explore(arr, i);
}

int main()
{
    int n, m;
    cin >> n >> m;

    visited.resize(n + 1, false);
    INT_MATRIX vertices(n + 1, vector<int>());
    
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        vertices[x].emplace_back(y);
    }

    topo_sort(vertices);
    reverse(answer.begin(), answer.end());
    
    for (const auto value : answer)
        cout << value << ' ';
}
