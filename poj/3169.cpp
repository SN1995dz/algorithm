#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int to, cost;
    edge() {}
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<edge> > G(n);
    for (int i = 0; i < n - 1; ++i) {
        G[i + 1].push_back(edge(i, 0));
    }
    while (a--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        G[x].push_back(edge(y, z));
    }
    while (b--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        G[y].push_back(edge(x, -z));
    }
    int S = 0;
    const int INF = 1e9 + 7;
    vector<int> d(n, INF);
    vector<bool> inque(n, false);
    vector<int> cnt(n, 0);
    queue<int> Q;
    d[S] = 0;
    inque[S] = true;
    Q.push(S);
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
    int ans;
    if (flag) {
        ans = -1;
    } else {
        if (d[n - 1] == INF) {
            ans = -2;
        } else {
            ans = d[n - 1];
        }
    }
    cout << ans << endl;
    return 0;
}

