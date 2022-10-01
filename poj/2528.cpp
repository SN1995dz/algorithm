#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class segtree {
    public:
        struct node {
            int val;
            int lazy;

            node() : val(0), lazy(-1) {}

            void apply(int l, int r, int v) {
                val = v;
                lazy = v;
            }
        };

        node unite(const node &a, const node &b) {
            node res;
            res.val = max(a.val, b.val);
            return res;
        }

        inline void push(int x, int l, int r) {
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            if (tree[x].lazy != -1) {
                tree[x + 1].apply(l, y, tree[x].lazy);
                tree[z].apply(y + 1, r, tree[x].lazy);
                tree[x].lazy = -1;
            }
        }

        inline void pull(int x, int z) {
            tree[x] = unite(tree[x + 1], tree[z]);
        }

        int n;
        node tree[80000];
        //vector<node> tree;

        void build(int x, int l, int r) {
            if (l == r) return;
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            build(x + 1, l, y);
            build(z, y + 1, r);
            pull(x, z);
        }

        template<typename T>
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
            if (ll <= l && r <= rr) {
                return tree[x];
            }
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
        
        template<typename T>
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

        //int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
        //    if (l == r) {
        //        return l;
        //    }
        //    push(x, l, r);
        //    int y = (l + r) >> 1;
        //    int z = x + ((y - l + 1) << 1);
        //    int res;
        //    if (f(tree[x + 1])) res = find_first_knowingly(x + 1, l, y, f);
        //    else res = find_first_knowingly(z, y + 1, r, f);
        //    pull(x, z);
        //    return res;
        //}

        //int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
        //    if (ll <= l && r <= rr) {
        //        if (!f(tree[x])) return -1;
        //        return find_first_knowingly(x, l, r, f);
        //    }
        //    push(x, l, r);
        //    int y = (l + r) >> 1;
        //    int z = x + ((y - l + 1) << 1);
        //    int res = -1;
        //    if (ll <= y) res = find_first(x + 1, l, y, ll, rr, f);
        //    if (rr > y && res == -1) res = find_first(z, y + 1, r, ll, rr, f);
        //    pull(x, z);
        //    return res;
        //}

        //int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
        //    if (l == r) {
        //        return l;
        //    }
        //    push(x, l, r);
        //    int y = (l + r) >> 1;
        //    int z = x + ((y - l + 1) << 1);
        //    int res;
        //    if (f(tree[z])) res = find_last_knowingly(z, y + 1, r, f);
        //    else res = find_last_knowingly(x + 1, l, y, f);
        //    pull(x, z);
        //    return res;
        //}

        //int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
        //    if (ll <= l && r <= rr) {
        //        if (!f(tree[x])) return -1;
        //        return find_last_knowingly(x, l, r, f);
        //    }
        //    push(x, l, r);
        //    int y = (l + r) >> 1;
        //    int z = x + ((y - l + 1) << 1);
        //    int res = -1;
        //    if (rr > y) res = find_last(z, y + 1, r, ll, rr, f);
        //    if (ll <= y && res == -1) res = find_last(x + 1, l, y, ll, rr, f);
        //    pull(x, z);
        //    return res;
        //}
    
        segtree(int _n) : n(_n) {
            assert(n > 0);
            //tree.resize(2 * n - 1);
            build(0, 0, n - 1);
        }

        template<typename T>
        segtree(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            //tree.resize(2 * n - 1);
            build(0, 0, n - 1, v);
        }

        node get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            return get(0, 0, n - 1, ll, rr);
        }

        node get(int p) {
            assert(0 <= p && p <= n - 1);
            return get(0, 0, n - 1, p, p);
        }

        template<typename T>
        void modify(int ll, int rr, const T &v) {
            assert(0 <= ll && ll <= rr && rr <= n - 1);
            modify(0, 0, n - 1, ll, rr, v);
        }
        
        template<typename T>
        void modify(int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            modify(0, 0, n - 1, p, p, v);
        }

        //int find_first(int ll, int rr, const function<bool(const node&)> &f) {
        //    assert(0 <= ll && ll <= rr && rr <= n - 1);
        //    return find_first(0, 0, n - 1, ll, rr, f);
        //}

        //int find_last(int ll, int rr, const function<bool(const node&)> &f) {
        //    assert(0 <= ll && ll <= rr && rr <= n - 1);
        //    return find_last(0, 0, n - 1, ll, rr, f);
        //}
};

pair<int, int> a[10000];
int h[40000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    segtree st(40000);
    while (T--) {
        int n;
        cin >> n;
        int m = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i].first >> a[i].second;
            h[m++] = a[i].first;
            h[m++] = a[i].second;
        }
        sort(h, h + m);
        for (int i = m - 1; i >= 1; --i) {
            if (h[i] > h[i - 1] + 1) {
                h[m++] = h[i] - 1;
            }
        }
        sort(h, h + m);
        m = unique(h, h + m) - h;
        st.modify(0, m - 1, 1);
        int ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            int l = lower_bound(h, h + m, a[i].first) - h;
            int r = lower_bound(h, h + m, a[i].second) - h;
            if (st.get(l, r).val == 1) {
                ++ans;
            }
            st.modify(l, r, 0);
        }
        cout << ans << endl;
    }
    return 0;
}

