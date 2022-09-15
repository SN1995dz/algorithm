#include <bits/stdc++.h>

using namespace std;

long long f[19][2520][48];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    set<int> S;
    map<int, int> M;
    function<long long(int, int, int, bool, bool)> dfs = [&](int pos, int mod, int p, bool smaller, bool positive) {
        if (pos < 0) {
            if (mod % p == 0) return (long long)positive;
            return 0LL;
        }
        if (smaller && positive && f[pos][mod][M[p]] != -1) return f[pos][mod][M[p]];
        long long res = 0;
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            int np = p;
            if (i != 0) {
                np = lcm(np, i);
            }
            res += dfs(pos - 1, (mod * 10 + i) % 2520, np, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][mod][M[p]] = res;
        return res;
    };
    auto solve = [&](long long x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        return dfs(a.size() - 1, 0, 1, false, false);
    };
    for (int mask = 1; mask < 1 << 9; ++mask) {
        int res = 1;
        for (int i = 1; i <= 9; ++i) {
            if (mask >> (i - 1) & 1) {
                res = lcm(res, i);
            }
        }
        S.insert(res);
    }
    int cnt = 0;
    for (auto x : S) {
        M[x] = cnt++;
    }
    memset(f, -1, sizeof(f));
    int T;
    cin >> T;
    while (T--) {
        long long l, r;
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}

