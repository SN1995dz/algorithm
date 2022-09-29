#include <iostream>
#include <vector>
#include <cassert>

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

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            if (l == 0) return get(r);
            return get(r) - get(l - 1);
        }

        int binary_search(T v) {
            int l = 0, r = n - 1, res = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (get(mid) >= v + 1) {
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
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<int> p(n), v(n);
        for (int i = 0; i < n; ++i) cin >> p[i] >> v[i];
        fenwick<int> fenw(n);
        for (int i = 0; i < n; ++i) fenw.modify(i, 1);
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; --i) {
            int tmp = fenw.binary_search(p[i]);
            ans[tmp] = v[i];
            assert(tmp != -1);
            fenw.modify(tmp, -1);
        }
        for (int i = 0; i < n; ++i) cout << ans[i] << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}

