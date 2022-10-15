#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];
    int k;
    cin >> k;
    long long ans = -1;
    vector<long long> sum(max(n, m) + 1, 0);
    auto answer = [&](vector<int>& c, int d) {
        if (d == 0) return 0LL;
        int len = c.size();
        for (int i = 0; i < len; ++i) {
            sum[i + 1] = sum[i] + c[i];
        }
        if (len <= d) return sum[len];
        long long res = sum[len];
        long long tmp = sum[len];
        long long num = 0;
        for (int r = 0, l = 0; r < len; ++r) {
            num += c[r];
            while (r - l + 1 > len - d) {
                num -= c[l];
                ++l;
            }
            if (r - l + 1 == len - d) {
                tmp = min(tmp, num);
            }
        }
        return res - tmp;
    };
    for (int i = 0; i <= k; ++i) {
        ans = max(ans, answer(a, i) + answer(b, k - i));
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

