#include <bits/stdc++.h>

using namespace std;

int f[1000][10][11][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a;
    const int MOD = 1e9 + 7;
    function<int(int, int, int, bool, bool, bool)> dfs = [&](int pos, int p, int pp, bool meng, bool smaller, bool positive) {
        if (pos < 0) {
            if (meng) return 1;
            return 0;
        }
        if (smaller && positive && f[pos][p][pp + 1][meng] != -1) return f[pos][p][pp + 1][meng];
        int res = 0, up = smaller ? 9 : a[pos] - '0';
        for (int i = 0; i <= up; ++i) {
            if (positive || i > 0) res = (res + dfs(pos - 1, i, p, meng || i == p || i == pp, smaller || i < up, positive || i > 0)) % MOD;
            else res = (res + dfs(pos - 1, -1, -1, meng || i == p || i == pp, smaller || i < up, positive || i > 0)) % MOD;
        }
        if (smaller && positive) f[pos][p][pp + 1][meng] = res;
        return res;
    };
    auto solve = [&](string x) {
        a = x;
        reverse(a.begin(), a.end());
        return dfs(a.length() - 1, -1, -1, false, false, false);
    };
    auto is_meng = [&](string s) {
        for (int i = 1; i < (int)s.length(); ++i) {
            if (s[i] == s[i - 1]) return 1;
        }
        for (int i = 2; i < (int)s.length(); ++i) {
            if (s[i] == s[i - 2]) return 1;
        }
        return 0;
    };
    string l, r;
    cin >> l >> r;
    memset(f, -1, sizeof(f));
    cout << ((solve(r) - solve(l) + MOD) % MOD + is_meng(l)) % MOD << endl;
    return 0;
}

