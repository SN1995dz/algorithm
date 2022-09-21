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

        vector<vector<int>> scc() {
            auto ids = scc_ids();
            int group_num = ids.first;
            vector<int> counts(group_num);
            for (auto x : ids.second) ++counts[x];
            vector<vector<int>> groups(ids.first);
            for (int i = 0; i < group_num; ++i) {
                groups[i].reserve(counts[i]);
            }
            for (int i = 0; i < n; ++i) {
                groups[ids.second[i]].push_back(i);
            }
            return groups;
        }

    private:
        int n;
        vector<vector<int>> G;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    scc_graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    auto scc = g.scc();
    cout << scc.size() << endl;
    for (auto v : scc) {
        cout << v.size();
        for (auto x : v) {
            cout << " " << x;
        }
        cout << endl;
    }
    return 0;
}

