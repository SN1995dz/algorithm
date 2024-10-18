#include <bits/stdc++.h>

using namespace std;

template<typename T> class Fenwick {
    public:
        vector<T> fenw;
        int n;

        Fenwick(int _n) : n(_n) {
            assert(n > 0);
            fenw.resize(_n);
        }

        Fenwick(vector<T> &a) {
            n = a.size();
            fenw.resize(n);
            for (int i = 0; i < n; ++i) {
                fenw[i] += a[i];
                int j = i | (i + 1);
                if (j < n) fenw[j] += fenw[i];
            }
        }

        void modify(int x, T v) {
            assert(0 <= x && x < n);
            while (x < n) {
                fenw[x] += v;
                x |= x + 1;
            }
        }

        T get(int p) {
            assert(0 <= p && p < n);
            T result = T();
            while (p >= 0) {
                result += fenw[p];
                p = (p & (p + 1)) - 1;
            }
            return result;
        }

        T get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr < n);
            if (ll == 0) return get(rr);
            return get(rr) - get(ll - 1);
        }

        // "smallest = v" or "biggest < v"; TO DO: optimize
        int binary_search(int ll, int rr, T v) {
            int l = ll, r = rr, res = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (get(ll, mid) >= v) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            return res;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<long long> d(n), e(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        d[i] = a[i];
        if (i > 0) d[i] -= a[i - 1];
        e[i] = (long long)a[i] * i;
        if (i > 0) e[i] -= (long long)a[i - 1] * i;
    }
    Fenwick<long long> f(d), g(e);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            f.modify(l, x);
            if (r + 1 < n) f.modify(r + 1, -x);
            g.modify(l, (long long)x * l);
            if (r + 1 < n) g.modify(r + 1, -(long long)x * (r + 1));
        } else {
            int l, r;
            cin >> l >> r;
            --l, --r;
            long long ans = f.get(l, r) * (r + 1) - g.get(l, r);
            if (l > 0) ans += f.get(0, l - 1) * (r - l + 1);
            cout << ans << endl;
        }
    }
    return 0;
}

