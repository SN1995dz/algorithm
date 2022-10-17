#include <bits/stdc++.h>

using namespace std;

struct eulerian_graph {
    public:
        explicit eulerian_graph(int _n) : n(_n), G(_n), d(_n, 0), D(_n, 0) {
            US.clear();
        }

        void add_edge(int u, int v) {
            assert(0 <= u && u < n);
            assert(0 <= v && v < n);
            G[u].push_back(v);
            G[v].push_back(u);
            US.insert(make_pair(u, v));
            US.insert(make_pair(v, u));
            ++d[u];
            ++d[v];
        }

        vector<int> eulerian_path(int start) {
            int odd = 0, tmp = 0;
            for (int i = 0; i < n; ++i) {
                if (d[i] % 2 == 1) {
                    ++odd;
                    tmp = i;
                }
            }
            if (start == -1) start = tmp;
            if (odd != 0 && odd != 2) return {-1};
            if (odd == 2 && d[start] % 2 == 0) return {-1};
            vector<int> res;
            stack<int> S;
            S.push(start);
            while (!S.empty()) {
                int u = S.top();
                if (d[u] == 0) {
                    res.push_back(u);
                    S.pop();
                    continue;
                }
                int v = G[u][D[u]];
                while (!US.count(make_pair(u, v))) {
                    ++D[u];
                    v = G[u][D[u]];
                }
                --d[u];
                --d[v];
                ++D[u];
                US.erase(US.find(make_pair(u, v)));
                US.erase(US.find(make_pair(v, u)));
                S.push(v);
            }
            if (!US.empty()) return {-1};
            return res;
        }

    private:
        int n;
        set<pair<int, int>> US;
        vector<vector<int>> G;
        vector<int> d;
        vector<int> D;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    eulerian_graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    vector<int> ans = g.eulerian_path(-1);
    if (ans[0] == -1) cout << "IMPOSSIBLE" << endl;
    else for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    return 0;
}

