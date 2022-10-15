#include <bits/stdc++.h>

using namespace std;

struct scc_graph {
    public:
        explicit scc_graph(int _n) : n(_n), G(_n) {}
        
        void add_edge(int from, int to) {
            assert(0 <= from && from < n);
            assert(0 <= to && to < n);
            G[from].push_back(to);
        }

        // @return pair of (# of scc, scc id)
        pair<int, vector<int>> scc_ids() {
            int now_ord = 0, group_num = 0;
            vector<int> visited, low(n), ord(n, -1), ids(n);
            visited.reserve(n);
            function<void(int)> tarjan = [&](int u) {
                low[u] = ord[u] = now_ord++;
                visited.push_back(u);
                for (int i = 0; i < (int)G[u].size(); ++i) {
                    int v = G[u][i];
                    if (ord[v] == -1) {
                        tarjan(v);
                        low[u] = min(low[u], low[v]);
                    } else {
                        low[u] = min(low[u], ord[v]);
                    }
                }
                if (low[u] == ord[u]) {
                    int top;
                    do {
                        top = visited.back();
                        visited.pop_back();
                        ord[top] = n;
                        ids[top] = group_num;
                    } while (top != u);
                    ++group_num;
                }
            };
            for (int i = 0; i < n; ++i) {
                if (ord[i] == -1) tarjan(i);
            }
            for (auto &x : ids) {
                x = group_num - 1 - x;
            }
            return {group_num, ids};
        }

    private:
        int n;
        vector<vector<int>> G;
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    scc_graph g(n);
    vector<int> u(m), v(m);
    for (int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        g.add_edge(u[i], v[i]);
    }
    auto ids = g.scc_ids();
    int N = ids.first;
    vector<int> cnt(N, 0);
    for (auto x : ids.second) ++cnt[x];
    set<pair<int, int>> S;
    vector<vector<int>> G(N);
    vector<int> din(N, 0);
    for (int i = 0; i < m; ++i) {
        int x = ids.second[u[i]], y = ids.second[v[i]];
        if (x == y) continue;
        if (!S.count(make_pair(x, y))) {
            S.insert(make_pair(x, y));
            G[x].push_back(y);
            ++din[y];
        }
    }
    queue<int> Q;
    for (int i = 0; i < N; ++i) {
        if (din[i] == 0) Q.push(i);
    }
    vector<set<int>> VS(N);
    for (int i = 0; i < n; ++i) {
        int col = ids.second[i];
        if ((int)VS[col].size() <= k) VS[col].insert(i);
    }
    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            for (auto e : VS[u]) {
                VS[v].insert(e);
                if ((int)VS[v].size() > k) break;
            }
            --din[v];
            if (din[v] == 0) Q.push(v);
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if ((int)VS[i].size() > k) {
            ans += cnt[i];
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

