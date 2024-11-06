#include <bits/stdc++.h>

using namespace std;

template<typename T> class SegTree {
    public:
        vector<int> rt;

        SegTree() = delete;

        SegTree(int sz, int _n) : n(_n), pool(1) {
            rt.clear();
            assert(n > 0);
            for (int i = 0; i < sz; ++i) rt.push_back(newNode());
        }

        SegTree(const vector<T> &v) : pool(1) {
            rt.clear();
            n = v.size();
            assert(n > 0);
            rt.push_back(newNode());
            function<void(int, int, int)> build = [&](int x, int l, int r) {
                if (l == r) {
                    pool[x].val = v[l];
                    return;
                }
                int y = (l + r) >> 1;
                pool[x].next[0] = newNode();
                pool[x].next[1] = newNode();
                build(pool[x].next[0], l, y);
                build(pool[x].next[1], y + 1, r);
                pool[x].val = pool[pool[x].next[0]].val + pool[pool[x].next[1]].val;
            };
            build(rt.back(), 0, n - 1);
        }
        
        int modify(int x, int ll, int rr, const T &v) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            rt.push_back(newNode());
            modify(x, rt.back(), 0, n - 1, ll, rr, v);
            return rt.back();
        }

        int modify(int x, int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            rt.push_back(newNode());
            modify(x, rt.back(), 0, n - 1, p, p, v);
            return rt.back();
        }
        
        T query(int x, int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return get(x, 0, n - 1, ll, rr);
        }

        T query(int x, int p) {
            assert(0 <= p && p <= n - 1);
            return get(x, 0, n - 1, p);
        }

    private:
        struct node {
            node() {
                val = T();
                lazy = T();
                next[0] = next[1] = 0;
            }
            
            T val;
            T lazy;
            array<int, 2> next;

            void apply(int l, int r, T v) {
                lazy += v;
            }
        };

        int n;
        vector<node> pool;

        int newNode() {
            pool.push_back({});
            return pool.size() - 1;
        }

        void modify(int x, int u, int l, int r, int ll, int rr, const T &v) {
            pool[u] = pool[x];
            if (ll <= l && r <= rr) {
                pool[u].apply(l, r, v);
                return;
            }
            int y = (l + r) >> 1;
            if (ll <= y) {
                pool[u].next[0] = newNode();
                modify(pool[x].next[0], pool[u].next[0], l, y, ll, rr, v);
            }
            if (rr > y) {
                pool[u].next[1] = newNode();
                modify(pool[x].next[1], pool[u].next[1], y + 1, r, ll, rr, v);
            }
            pool[u].val += v * (min(rr, r) - max(ll, l) + 1);
        }

        T get(int x, int l, int r, int ll, int rr) {
            if (ll <= l && r <= rr) {
                return pool[x].val + pool[x].lazy * (r - l + 1);
            }
            int y = (l + r) >> 1;
            T res = pool[x].lazy * (min(rr, r) - max(ll, l) + 1);
            if (ll <= y) res += get(pool[x].next[0], l, y, ll, rr);
            if (rr > y) res += get(pool[x].next[1], y + 1, r, ll, rr);
            return res;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        SegTree<long long> st(a);
        vector<int> roots(1, st.rt[0]);
        int curTime = 0;
        while (m--) {
            string op;
            cin >> op;
            if (op[0] == 'C') {
                int l, r, d;
                cin >> l >> r >> d;
                --l, --r;
                roots.push_back(st.modify(roots[curTime], l, r, d));
                ++curTime;
            } else if (op[0] == 'Q') {
                int l, r;
                cin >> l >> r;
                --l, --r;
                cout << st.query(roots[curTime], l, r) << endl;
            } else if (op[0] == 'H') {
                int l, r, t;
                cin >> l >> r >> t;
                --l, --r;
                cout << st.query(roots[t], l, r) << endl;
            } else {
                int t;
                cin >> t;
                curTime = t;
                roots.resize(curTime + 1);
            }
        }
    }
    return 0;
}

