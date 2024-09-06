#include <bits/stdc++.h>

using namespace std;

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
    const int MOD = 1e9 + 7;
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
            }
        }
        string s;
        cin >> s;
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            string t;
            for (int j = i; j < n; ++j) t.push_back(s[j]);
            t.push_back('#');
            t += s;
            vector<int> z = zFunction(t);
            int m = n - i;
            vector<int> num(m + 1, 0);
            for (int j = m + 1; j < m + n + 1; ++j) {
                ++num[z[j]];
            }
            for (int j = m; j > 0; --j) {
                ++cnt[num[j]];
                num[j - 1] += num[j];
            }
        }
        for (int i = 1; i <= n; ++i) cnt[i] /= i;
        vector<int> res(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                res[i] = (res[i] + (long long)C[j][i] * cnt[j] % MOD) % MOD;
            }
        }
        while (q--) {
            int k;
            cin >> k;
            if (k > n) {
                cout << 0 << endl;
                continue;
            }
            cout << res[k] << endl;
        }
    }
    return 0;
}

