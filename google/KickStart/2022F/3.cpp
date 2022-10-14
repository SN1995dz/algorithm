#include <bits/stdc++.h>

using namespace std;

template<typename T> class fenwick {
    public:
        vector<T> fenw;
        int n;

        fenwick(int _n) : n(_n) {
            assert(n > 0);
            fenw.resize(_n);
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int n, k, x, d;
        cin >> n >> k >> x >> d;
        int m;
        cin >> m;
        vector<pair<int, int>> a, b;
        for (int i = 0; i < m; ++i) {
            int p, l, r;
            cin >> p >> l >> r;
            --p;
            a.push_back(make_pair(l, p));
            b.push_back(make_pair(r, p));
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int ans = m;
        fenwick<int> cnt(m + 1), sum(m + 1);
        cnt.modify(0, n);
        vector<int> c(n, 0);
        for (int l = 0, r = 0, pa = 0, pb = 0; l <= d - x; ++l) {
            while (r < l + x) {
                ++r;
                while (pa < m && a[pa].first < r) {
                    int p = a[pa].second;
                    cnt.modify(c[p], -1);
                    sum.modify(c[p], -c[p]);
                    ++c[p];
                    cnt.modify(c[p], 1);
                    sum.modify(c[p], c[p]);
                    ++pa;
                }
            }
            int ll = 0, rr = m, res = -1;
            while (ll <= rr) {
                int mid = (ll + rr) / 2;
                if (cnt.get(mid) <= k) {
                    res = mid;
                    ll = mid + 1;
                } else {
                    rr = mid - 1;
                }
            }
            if (res == -1) ans = min(ans, 0);
            else ans = min(ans, sum.get(res) + (k - cnt.get(res)) * (res + 1));
            while (pb < m && b[pb].first <= l + 1) {
                int p = b[pb].second;
                cnt.modify(c[p], -1);
                sum.modify(c[p], -c[p]);
                --c[p];
                cnt.modify(c[p], 1);
                sum.modify(c[p], c[p]);
                ++pb;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

