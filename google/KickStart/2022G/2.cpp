#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> s(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] + a[i];
    }
    vector<long long> b(n + 2, 0);
    for (int i = 0; i <= n; ++i) {
        b[i + 1] = b[i] + s[i];
    }
    vector<vector<int>> f(n + 1, vector<int>(20));
    for (int i = 1; i <= n; ++i) f[i][0] = s[i];
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    auto rmq = [&](int l, int r) {
        int k = log2(r - l + 1);
        return min(f[l][k], f[r - (1 << k) + 1][k]);
    };
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = i, r = n, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (rmq(i, mid) - s[i - 1] >= 0) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (res == -1) continue;
        ans += b[res + 1] - b[i] - (long long)(res - i + 1) * s[i - 1];
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

