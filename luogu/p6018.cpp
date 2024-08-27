#include <bits/stdc++.h>

using namespace std;

class Trie01 {
    public:
        vector<int> rt;

        Trie01() = delete;

        Trie01(int sz) : pool(1) {
            for (int i = 0; i < sz; ++i) rt.push_back(newNode());
        }

        void maintain(int u) {
            pool[u].cnt = 0;
            pool[u].xorv = 0;
            if (pool[u].next[0]) {
                pool[u].cnt += pool[pool[u].next[0]].cnt;
                pool[u].xorv ^= pool[pool[u].next[0]].xorv << 1;
            }
            if (pool[u].next[1]) {
                pool[u].cnt += pool[pool[u].next[1]].cnt;
                pool[u].xorv ^= pool[pool[u].next[1]].xorv << 1 | (pool[pool[u].next[1]].cnt & 1);
            }
        }

        // x: int/long long
        void insert(int u, int x, int depth=0) {
            if (depth == MAXBIT) {
                ++pool[u].cnt;
                return;
            }
            if (!pool[u].next[x & 1]) pool[u].next[x & 1] = newNode();
            insert(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }
        
        // x: int/long long
        void erase(int u, int x, int depth=0) {
            if (depth == MAXBIT) {
                --pool[u].cnt;
                return;
            }
            erase(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }

        void addAll(int u) {
            swap(pool[u].next[0], pool[u].next[1]);
            if (pool[u].next[0]) addAll(pool[u].next[0]);
            maintain(u);
        }

        int getXor(int u) {
            return pool[u].xorv;
        }

        int merge(int a, int b) {
            if (!a) return b;
            if (!b) return a;
            pool[a].cnt += pool[b].cnt;
            pool[a].xorv ^= pool[b].xorv;
            pool[a].next[0] = merge(pool[a].next[0], pool[b].next[0]);
            pool[a].next[1] = merge(pool[a].next[1], pool[b].next[1]);
            return a;
        }
        
    private:
        // MAXBIT: int/long long
        const int MAXBIT = 21;
        struct node {
            node() : cnt(0), xorv(0) {
                next[0] = next[1] = 0;
            }
            int cnt, xorv;
            int next[2];
        };
        vector<node> pool;

        int newNode() {
           pool.push_back({});
           return pool.size() - 1;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> par(n, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
        par[u] = p;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == p) continue;
            dfs(v, u);
        }
    };
    dfs(0, -1);
    vector<int> val(n);
    Trie01 T(n);
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
        if (par[i] != -1) T.insert(T.rt[par[i]], val[i]);
    }
    vector<int> lazy(n, 0);
    auto get = [&](int x) {
        if (par[x] != -1) return lazy[par[x]] + val[x];
        return val[x];
    };
    auto add = [&](int u, int v) {
        if (par[u] != -1) T.erase(T.rt[par[u]], get(u));
        val[u] += v;
        if (par[u] != -1) T.insert(T.rt[par[u]], get(u));
    };
    while (m--) {
        int op, x;
        cin >> op >> x;
        --x;
        if (op == 1) {
            if (par[x] != -1) add(par[x], 1);
            ++lazy[x];
            T.addAll(T.rt[x]);
        } else if (op == 2) {
            int v;
            cin >> v;
            add(x, -v);
        } else {
            int res = T.getXor(T.rt[x]);
            if (par[x] != -1) res ^= get(par[x]);
            cout << res << endl;
        }
    }
    return 0;
}

