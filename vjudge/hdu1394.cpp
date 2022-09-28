#include <bits/stdc++.h>

using namespace std;

template<typename T>
class segtree {
    public:
        struct node {
            // -1 0
            T val = 0;
            bool put = false;

            void apply(int l, int r, T v) {
                // = +=
                val += v;
                put = true;
            }
        };

        node unite(const node &a, const node &b) {
            node res;
            // max a+b
            res.val = a.val + b.val;
            return res;
        }

        inline void push(int x, int l, int r) {
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            if (tree[x].put) {
                tree[x + 1].apply(l, y, tree[x].val);
                tree[z].apply(y + 1, r, tree[x].val);
                tree[x].put = false;
            }
        }

        inline void pull(int x, int z) {
            tree[x] = unite(tree[x + 1], tree[z]);
        }

        int n;
        vector<node> tree;

        void build(int x, int l, int r) {
            if (l == r) return;
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            build(x + 1, l, y);
            build(z, y + 1, r);
            pull(x, z);
        }

        void build(int x, int l, int r, const vector<T> &v) {
            if (l == r) {
                tree[x].apply(l, r, v[l]);
                return;
            }
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            build(x + 1, l, y, v);
            build(z, y + 1, r, v);
            pull(x, z);
        }

        node get(int x, int l, int r, int ll, int rr) {
            if (ll <= l && r <= rr) return tree[x];
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            push(x, l, r);
            node res;
            if (rr <= y) {
                res = get(x + 1, l, y, ll, rr);
            } else {
                if (ll > y) {
                    res = get(z, y + 1, r, ll, rr);
                } else {
                    res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
                }
            }
            pull(x, z);
            return res;
        }

        void modify(int x, int l, int r, int ll, int rr, const T &v) {
            if (ll <= l && r <= rr) {
                tree[x].apply(l, r, v);
                return;
            }
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            push(x, l, r);
            if (ll <= y) modify(x + 1, l, y, ll, rr, v);
            if (rr > y) modify(z, y + 1, r, ll, rr, v);
            pull(x, z);
        }
        
        segtree(int _n) : n(_n) {
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1);
        }

        segtree(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1, v);
        }

        T get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return get(0, 0, n - 1, ll, rr).val;
        }

        T get(int p) {
            assert(0 <= p && p <= n - 1);
            return get(0, 0, n - 1, p, p).val;
        }

        void modify(int ll, int rr, const T &v) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            modify(0, 0, n - 1, ll, rr, v);
        }

        void modify(int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            modify(0, 0, n - 1, p, p, v);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        segtree<int> st(n);
        int ans = 0;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] + 1 <= n - 1) ans += st.get(a[i] + 1, n - 1);
            st.modify(a[i], 1);
        }
        int res = ans;
        for (int i = 0; i < n - 1; ++i) {
            res -= a[i];
            res += n - 1 - a[i];
            ans = min(ans, res);
        }
        cout << ans << endl;
    }
    return 0;
}

