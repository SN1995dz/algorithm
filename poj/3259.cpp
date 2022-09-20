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
    int T;
    cin >> T;
    while (T--) {
        int n, m, w;
        cin >> n >> m >> w;
        vector<vector<edge> > G(n);
        while (m--) {
            int x, y, z;
            cin >> x >> y >> z;
            --x, --y;
            G[x].push_back(edge(y, z));
            G[y].push_back(edge(x, z));
        }
        while (w--) {
            int x, y, z;
            cin >> x >> y >> z;
            --x, --y;
            G[x].push_back(edge(y, -z));
        }
        vector<int> d(n, 0);
        queue<int> Q;
        for (int i = 0; i < n; ++i) Q.push(i);
        vector<int> cnt(n, 0);
        vector<bool> inque(n, true);
        bool flag = false;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inque[u] = false;
            if (cnt[u] == n) {
                flag = true;
                break;
            }
            for (int i = 0; i < (int)G[u].size(); ++i) {
                edge e = G[u][i];
                int v = e.to;
                if (d[v] > d[u] + e.cost) {
                    d[v] = d[u] + e.cost;
                    ++cnt[v];
                    if (!inque[v]) {
                        Q.push(v);
                        inque[v] = true;
                    }
                }
            }
        }
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

