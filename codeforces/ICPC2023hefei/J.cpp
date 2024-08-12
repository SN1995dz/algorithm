#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, cost;
    edge(int _to, int _cost) : to(_to), cost(_cost) {}
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
            if (d[v] > max(d[u], e.cost)) {
                d[v] = max(d[u], e.cost);
                pq.push(make_pair(d[v], v));
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> G(n);
    vector<int> u(m), v(m), w(m);
    for (int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        --u[i], --v[i];
        G[u[i]].push_back(edge(v[i], w[i]));
        G[v[i]].push_back(edge(u[i], w[i]));
    }
    int S = 0;
    vector<int> d = dijkstra(G, S);
    S = n - 1;
    vector<int> invd = dijkstra(G, S);
    int ans = 2e9;
    for (int i = 0; i < m; ++i) {
        if (d[u[i]] <= w[i] && invd[v[i]] <= w[i]) {
            ans = min(ans, w[i] + max(d[u[i]], invd[v[i]]));
        }
        if (d[v[i]] <= w[i] && invd[u[i]] <= w[i]) {
            ans = min(ans, w[i] + max(d[v[i]], invd[u[i]]));
        }
    }
    cout << ans << endl;
    return 0;
}

