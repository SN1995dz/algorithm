#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, cost, price;
    edge(int to, int cost, int price) : to(to), cost(cost), price(price) {}
};

const int INF = 1e9;

vector<int> dijkstra(vector<vector<edge>> &G, int S) {
    int n = G.size();
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
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        int S = 0;
        vector<vector<edge>> G(n);
        while (m--) {
            int u, v, d, c;
            cin >> u >> v >> d >> c;
            --u, --v;
            G[u].push_back(edge(v, d, c));
            G[v].push_back(edge(u, d, c));
        }
        vector<int> d = dijkstra(G, S);
        int ans = 0;
        for (int v = 1; v < n; ++v) {
            int res = INF;
            for (int i = 0; i < (int)G[v].size(); ++i) {
                auto e = G[v][i];
                int u = e.to;
                if (d[u] + e.cost == d[v]) {
                    res = min(res, e.price);
                }
            }
            ans += res;
        }
        cout << ans << endl;
    }
    return 0;
}

