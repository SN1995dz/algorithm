#include <bits/stdc++.h>

using namespace std;

template<typename T> class SegTree {
    public:
        SegTree(int _n) : n(_n) {
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1);
        }

        SegTree(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1, v);
        }
        
        void modify(int ll, int rr, const T &v) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            modify(0, 0, n - 1, ll, rr, v);
        }
        
        void modify(int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            modify(0, 0, n - 1, p, p, v);
        }

        T get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return get(0, 0, n - 1, ll, rr).val;
        }

        T get(int p) {
            assert(0 <= p && p <= n - 1);
            return get(0, 0, n - 1, p, p).val;
        }

    private:
        struct node {
            T val = T();
            T lazy = T();
            bool ifLazy = false;

            void apply(int l, int r, T v) {
                val += v * (r - l + 1);
                lazy += v;
                ifLazy = true;
            }
        };
        
        int n;
        vector<node> tree;

        node unite(const node &a, const node &b) {
            node res;
            res.val = a.val + b.val;
            return res;
        }

        inline void push(int x, int l, int r) {
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            if (tree[x].ifLazy) {
                tree[x + 1].apply(l, y, tree[x].lazy);
                tree[z].apply(y + 1, r, tree[x].lazy);
                tree[x].lazy = T();
                tree[x].ifLazy = false;
            }
        }

        inline void pull(int x, int z) {
            tree[x] = unite(tree[x + 1], tree[z]);
        }


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
        
        // TODO: lack organization
        int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
            if (l == r) {
                return l;
            }
            push(x, l, r);
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            int res;
            if (f(tree[x + 1])) res = find_first_knowingly(x + 1, l, y, f);
            else res = find_first_knowingly(z, y + 1, r, f);
            pull(x, z);
            return res;
        }

        int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
            if (ll <= l && r <= rr) {
                if (!f(tree[x])) return -1;
                return find_first_knowingly(x, l, r, f);
            }
            push(x, l, r);
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            int res = -1;
            if (ll <= y) res = find_first(x + 1, l, y, ll, rr, f);
            if (rr > y && res == -1) res = find_first(z, y + 1, r, ll, rr, f);
            pull(x, z);
            return res;
        }

        int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
            if (l == r) {
                return l;
            }
            push(x, l, r);
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            int res;
            if (f(tree[z])) res = find_last_knowingly(z, y + 1, r, f);
            else res = find_last_knowingly(x + 1, l, y, f);
            pull(x, z);
            return res;
        }

        int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
            if (ll <= l && r <= rr) {
                if (!f(tree[x])) return -1;
                return find_last_knowingly(x, l, r, f);
            }
            push(x, l, r);
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            int res = -1;
            if (rr > y) res = find_last(z, y + 1, r, ll, rr, f);
            if (ll <= y && res == -1) res = find_last(x + 1, l, y, ll, rr, f);
            pull(x, z);
            return res;
        }

        int find_first(int ll, int rr, const function<bool(const node&)> &f) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return find_first(0, 0, n - 1, ll, rr, f);
        }

        int find_last(int ll, int rr, const function<bool(const node&)> &f) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return find_last(0, 0, n - 1, ll, rr, f);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegTree st(a);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            long long k;
            cin >> x >> y >> k;
            --x, --y;
            st.modify(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            --x, --y;
            cout << st.get(x, y) << endl;
        }
    }
    return 0;
}

