#include <bits/stdc++.h>

using namespace std;

template<typename T> class SegTree {
    public:
        vector<int> rt;

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
        
        int modify(int x, int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            rt.push_back(newNode());
            modify(x, rt.back(), 0, n - 1, p, p, v);
            return rt.back();
        }
        
        T query(int x, int u, int k) {
            assert(1 <= k && k <= pool[u].val - pool[x].val);
            return query(x, u, k, 0, n - 1);
        }

    private:
        struct node {
            node() {
                val = T();
                next[0] = next[1] = 0;
            }
            
            T val;
            array<int, 2> next;

            void apply(int l, int r, T v) {
                val += v;
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

        T query(int x, int u, int k, int l, int r) {
            if (l == r) return l;
            int y = (l + r) >> 1;
            T tmp = pool[pool[u].next[0]].val - pool[pool[x].next[0]].val;
            T res;
            if (tmp >= k) res = query(pool[x].next[0], pool[u].next[0], k, l, y);
            else res = query(pool[x].next[1], pool[u].next[1], k - tmp, y + 1, r);
            return res;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    vector<int> c(b.size(), 0);
    SegTree<int> st(c);
    for (int i = 0; i < n; ++i) st.modify(st.rt[i], a[i], 1);
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << b[st.query(st.rt[l - 1], st.rt[r], k)] << endl;
    }
    return 0;
}

