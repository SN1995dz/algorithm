#include <iostream>
#include <vector>
#include <cassert>

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
        pair<int, vector<int> > scc_ids() {
            now_ord = 0, group_num = 0;
            low.resize(n), ord.resize(n, -1), ids.resize(n);
            visited.reserve(n);
            for (int i = 0; i < n; ++i) {
                if (ord[i] == -1) tarjan(i);
            }
            for (int i = 0; i < (int)ids.size(); ++i) {
                ids[i] = group_num - 1 - ids[i];
            }
            /*for (auto &x : ids) {
                x = group_num - 1 - x;
            }*/
            return make_pair(group_num, ids);
        }

        /*vector<vector<int>> scc() {
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
        }*/

    private:
        int n;
        vector<vector<int> > G;
        
        int now_ord, group_num;
        vector<int> visited, low, ord, ids;
        void tarjan(int u) {
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    scc_graph g(n);
    vector<int> u, v;
    for (int i = 0; i < n; ++i) {
        while (true) {
            int x;
            cin >> x;
            if (x == 0) break;
            --x;
            u.push_back(i);
            v.push_back(x);
            g.add_edge(i, x);
        }
    }
    pair<int, vector<int> > scc_ids = g.scc_ids();
    vector<int> din(scc_ids.first, 0), dout(scc_ids.first, 0);
    for (int i = 0; i < (int)u.size(); ++i) {
        if (scc_ids.second[u[i]] != scc_ids.second[v[i]]) {
            ++din[scc_ids.second[v[i]]];
            ++dout[scc_ids.second[u[i]]];
        }
    }
    int task1 = 0, task2 = 0;
    for (int i = 0; i < scc_ids.first; ++i) {
        if (din[i] == 0) ++task1;
        if (dout[i] == 0) ++task2;
    }
    cout << task1 << endl;
    cout << (scc_ids.first == 1 ? 0 : max(task1, task2)) << endl;
    return 0;
}

