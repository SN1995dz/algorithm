#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    vector<vector<edge>> G(10);
    while (true) {
        cin >> m;
        if (m == 0) break;
        for (int i = 0; i < 10; ++i) G[i].clear();
        int n = 2;
        while (m--) {
            int x, y, z;
            cin >> x >> y >> z;
            G[x].push_back(edge(y, z));
            G[y].push_back(edge(x, z));
            n = max(n, x + 1);
            n = max(n, y + 1);
        }
        int ans = 1e9, ansid = -1;
        for (int i = 0; i < n; ++i) {
            int S = i;
            vector<int> d(n, 1e9);
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
            int res = 0;
            for (int j = 0; j < n; ++j) {
                res += d[j];
            }
            if (res < ans) {
                ans = res;
                ansid = i;
            }
        }
        cout << ansid << " " << ans << endl;
    }
    return 0;
}

