#include <bits/stdc++.h>

using namespace std;

template<typename T> class SparseTable {
    public:
        SparseTable(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            g.resize(n, vector<int>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) {
                f[i][0] = v[i];
                g[i][0] = i;
            }
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    if (f[i][j - 1] < f[i + (1 << (j - 1))][j - 1]) {
                        f[i][j] = f[i][j - 1];
                        g[i][j] = g[i][j - 1];
                    } else {
                        f[i][j] = f[i + (1 << (j - 1))][j - 1];
                        g[i][j] = g[i + (1 << (j - 1))][j - 1];
                    }
                }
            }
        }

        int get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            if (f[l][k] < f[r - (1 << k) + 1][k]) return g[l][k];
            return g[r - (1 << k) + 1][k];
        }

    private:
        int n;
        vector<vector<T>> f;
        vector<vector<int>> g; // for argmin

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }
};

template<typename T> class SegTree {
    public:
        vector<int> rt;

        SegTree() = delete;

        SegTree(int sz, int _n) : pool(1), n(_n) {
            rt.clear();
            assert(n > 0);
            for (int i = 0; i < sz; ++i) rt.push_back(newNode());
        }

        void modify(int x, int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            modify(x, 0, n - 1, p, v);
        }
        
        int query(int x) {
            return query(x, 0, n - 1);
        }

        void merge(int x, int u) {
            merge(x, u, 0, n - 1);
        }

    private:
        struct node {
            node() {
                val = T();
                next[0] = next[1] = 0;
            }
            
            T val;
            array<int, 2> next;
        };

        vector<node> pool;
        int n;

        int newNode() {
            pool.push_back({});
            return pool.size() - 1;
        }

        inline void pull(int x) {
            int L = 0, R = 0;
            if (pool[x].next[0]) L = pool[pool[x].next[0]].val;
            if (pool[x].next[1]) R = pool[pool[x].next[1]].val;
            pool[x].val = max(L, R);
        }

        void modify(int x, int l, int r, int p, const T &v) {
            if (l == r) {
                pool[x].val += v;
                return;
            }
            int y = (l + r) >> 1;
            if (p <= y) {
                if (!pool[x].next[0]) pool[x].next[0] = newNode();
                modify(pool[x].next[0], l, y, p, v);
            } else {
                if (!pool[x].next[1]) pool[x].next[1] = newNode();
                modify(pool[x].next[1], y + 1, r, p, v);
            }
            pull(x);
        }

        int query(int x, int l, int r) {
            if (pool[x].val == 0) return -1;
            if (l == r) return l;
            int y = (l + r) >> 1;
            int L = 0, R = 0;
            if (pool[x].next[0]) L = pool[pool[x].next[0]].val;
            if (pool[x].next[1]) R = pool[pool[x].next[1]].val;
            if (L >= R) return query(pool[x].next[0], l, y);
            else return query(pool[x].next[1], y + 1, r);
            return -1;
        }

        int merge(int a, int b, int l, int r) {
            if (!a) return b;
            if (!b) return a;
            if (l == r) {
                pool[a].val += pool[b].val;
                return a;
            }
            int y = (l + r) >> 1;
            pool[a].next[0] = merge(pool[a].next[0], pool[b].next[0], l, y);
            pool[a].next[1] = merge(pool[a].next[1], pool[b].next[1], y + 1, r);
            pull(a);
            return a;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    int rt = 0;
    vector<int> pos(n);
    vector<int> vs, depth;
    vector<int> par(n);
    function<void(int, int, int)> dfs = [&](int u, int p, int d) {
        pos[u] = vs.size();
        par[u] = p;
        vs.push_back(u);
        depth.push_back(d);
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == p) continue;
            dfs(v, u, d + 1);
            vs.push_back(u);
            depth.push_back(d);
        }
    };
    dfs(rt, -1, 0);
    SparseTable<int> ST(depth);
    auto lca = [&](int u, int v) {
        return vs[ST.get(min(pos[u], pos[v]), max(pos[u], pos[v]))];
    };
    const int N = 1e5;
    SegTree<int> st(n, N);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y, --z;
        int p = lca(x, y);
        st.modify(st.rt[x], z, 1);
        st.modify(st.rt[y], z, 1);
        st.modify(st.rt[p], z, -1);
        if (p != 0) st.modify(st.rt[par[p]], z, -1);
    }
    vector<int> ans(n, 0);
    function<void(int, int)> calc = [&](int u, int p) {
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == p) continue;
            calc(v, u);
            st.merge(st.rt[u], st.rt[v]);
        }
        ans[u] = st.query(st.rt[u]);
    };
    calc(rt, -1);
    for (int i = 0; i < n; ++i) cout << ans[i] + 1 << endl;
    return 0;
}

