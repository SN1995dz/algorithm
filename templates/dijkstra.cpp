#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const int INF = 1e9;
    int n, m, S = ...;
    vector<vector<edge>> G(n);
    ... //edges
    vector<int> d(n, INF);
    d[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int u = p.second;
        if (d[u] < p.first) continue;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            auto e = G[u][i];
            int v = e.to;
            if (d[v] > p.first + e.cost) {
                d[v] = p.first + e.cost;
                pq.push(make_pair(d[v], v));
            }
        }
    }
    return 0;
}

