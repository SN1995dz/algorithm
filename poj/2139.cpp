#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<edge> > G(n);
    while (m--) {
        int mi;
        cin >> mi;
        vector<int> a(mi);
        for (int i = 0; i < mi; ++i) cin >> a[i], --a[i];
        for (int i = 0; i < mi; ++i) {
            for (int j = i + 1; j < mi; ++j) {
                G[a[i]].push_back(edge(a[j], 1));
                G[a[j]].push_back(edge(a[i], 1));
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < n; ++i) {
        int S = i;
        vector<int> d(n, 1e9);
        d[S] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(0, S));
        while (!pq.empty()) {
            pair<int, int> p = pq.top();
            pq.pop();
            int u = p.second;
            if (d[u] < p.first) continue;
            for (int i = 0; i < (int)G[u].size(); ++i) {
                edge e = G[u][i];
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
        ans = min(ans, res * 100 / (n - 1));
    }
    cout << ans << endl;
    return 0;
}

