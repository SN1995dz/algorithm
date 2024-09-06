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

        // "smallest = v" or "biggest < v"
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

// z[i] = max{x}->a[0..x-1]=a[i..i+x-1]
template<typename T>
vector<int> zFunction(const T& a) {
    int n = a.size();
    vector<int> z(n);
    z[0] = n;
    int l = -1, r = -1;
    for (int i = 1; i < n; ++i) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < n && a[i + z[i]] == a[z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    vector<int> z = zFunction(s);
    int n = z.size();
    vector<pair<int, int>> ans;
    ans.push_back(make_pair(n, 1));
    fenwick<int> fenw(n);
    for (int i = 1; i < n; ++i) {
        if (z[i] == n - i) {
            ans.push_back(make_pair(n - i, fenw.get(z[i], n - 1) + 2));
        }
        fenw.modify(z[i], 1);
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}

