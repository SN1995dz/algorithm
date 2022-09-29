//#include <iostream>
#include <cstdio>
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

        T get(int ll, int rr) {
            assert(0 <= ll && ll <= rr && rr < n);
            if (ll == 0) return get(rr);
            return get(rr) - get(ll - 1);
        }

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

const int N = 500000;
char name[N][11];

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    vector<int> res(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; j += i) {
            ++res[j];
        }
    }
    int n, k;
    //while (cin >> n >> k) {
    while (~scanf("%d%d", &n, &k)) {
        --k;
        //vector<string> name(n);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            //cin >> name[i] >> a[i];
            scanf("%s%d", name[i], &a[i]);
        }
        fenwick<int> fenw(n);
        for (int i = 0; i < n; ++i) fenw.modify(i, 1);
        /*vector<int> res(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; j += i) {
                ++res[j];
            }
        }*/
        int ans = 0, p = -1;
        for (int i = 0; i < n; ++i) {
            if (res[i + 1] > ans) {
                ans = res[i + 1];
                p = k;
            }
            if (i == n - 1) break;
            fenw.modify(k, -1);
            if (a[k] > 0) {
                a[k] %= n - i - 1;
                if (a[k] == 0) a[k] = n - i - 1;
            } else {
                a[k] = -a[k];
                a[k] %= n - i - 1;
                if (a[k] == 0) a[k] = n - i - 1;
                a[k] = n - i - a[k];
            }
            int tmp = (k == n - 1 ? 0 : fenw.get(k + 1, n - 1));
            if (tmp >= a[k]) {
                k = fenw.binary_search(k + 1, n - 1, a[k]);
            } else {
                a[k] -= tmp;
                k = fenw.binary_search(0, k - 1, a[k]);
            }
        }
        //cout << name[p] << " " << ans << endl;
        printf("%s %d\n", name[p], ans);
    }
    return 0;
}

