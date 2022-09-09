#include <bits/stdc++.h>

using namespace std;

// @param m '1 <= m'
// @return x mod m
long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// @param n '0 <= n'
// @param m '1 <= m'
// @return '(x ** n) % m'
long long pow_mod(long long x, long long n, int m) {
    assert(0 <= n && 1 <= m);
    if (m == 1) return 0;
    long long r = 1, y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = r * y % m;
        y = y * y % m;
        n >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    long long ans = 1;
    const int MOD = 1e7 + 7;
    vector<vector<vector<long long>>> f(51, vector<vector<long long>>(51, vector<long long>(51, -1)));
    function<long long(int, int, int, bool, bool)> dfs = [&](int pos, int cnt, int tar, bool smaller, bool positive) {
        if (pos < 0) return (long long)(cnt == tar);
        if (smaller && positive && f[pos][cnt][tar] != -1) return f[pos][cnt][tar];
        long long res = 0;
        int up = smaller ? 1 : a[pos];
        for (int i = 0; i <= up; ++i) {
            res += dfs(pos - 1, cnt + (i == 1), tar, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][cnt][tar] = res;
        return res;
    };
    auto solve = [&](long long x) {
        a.clear();
        while (x) {
            a.push_back(x % 2);
            x /= 2;
        }
        for (int i = 1; i <= (int)a.size(); ++i) {
            ans = ans * pow_mod(i, dfs(a.size() - 1, 0, i, false, false), MOD) % MOD;
        }
    };
    long long n;
    cin >> n;
    solve(n);
    cout << ans << endl;
    return 0;
}

