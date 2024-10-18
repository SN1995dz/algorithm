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
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<long long> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        d[i] = a[i];
        if (i > 0) d[i] -= a[i - 1];
    }
    Fenwick<long long> f(d);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            f.modify(l, x);
            if (r + 1 < n) f.modify(r + 1, -x);
        } else {
            int p;
            cin >> p;
            --p;
            cout << f.get(0, p) << endl;
        }
    }
    return 0;
}

