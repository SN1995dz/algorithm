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
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    Fenwick<long long> f(a);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            --x;
            f.modify(x, y);
        } else {
            --x, --y;
            cout << f.get(x, y) << endl;
        }
    }
    return 0;
}

