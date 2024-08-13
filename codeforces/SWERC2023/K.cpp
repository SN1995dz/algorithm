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
 
        T get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr < n);
            if (ll == 0) return get(rr);
            return get(rr) - get(ll - 1);
        }
 
        // v+1->v : v-th->next(v)
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
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n / 2), b(n / 2);
    for (int i = 0; i < n / 2; ++i) cin >> a[i];
    for (int i = 0; i < n / 2; ++i) cin >> b[i];
    vector<int> ansa, ansb;
    fenwick<int> fenw(n);
    for (int i = 0; i < n; ++i) fenw.modify(i, 1);
    for (int i = 0; i < n / 2; ++i) {
        int tmp = fenw.binary_search(0, n - 1, a[i]);
        ansa.push_back(tmp + 1);
        fenw.modify(tmp, -1);
        tmp = fenw.binary_search(0, n - 1, b[i]);
        ansb.push_back(tmp + 1);
        fenw.modify(tmp, -1);
    }
    for (int i = 0; i < n / 2; ++i) cout << ansa[i] << " ";
    cout << endl;
    for (int i = 0; i < n / 2; ++i) cout << ansb[i] << " ";
    cout << endl;
    return 0;
}

