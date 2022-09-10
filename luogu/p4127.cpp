#include <bits/stdc++.h>

using namespace std;

long long f[18][163][162];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    function<long long(int, int, int, bool, bool, int)> dfs = [&](int pos, int s, int mod, bool smaller, bool positive, int S) {
        if (pos < 0) {
            if (s == 0 && mod == 0) return 1LL;
            return 0LL;
        }
        if (smaller && positive && f[pos][s][mod] != -1) return f[pos][s][mod];
        long long res = 0;
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            if (s - i < 0) break;
            res += dfs(pos - 1, s - i, (mod * 10 + i) % S, smaller || i < up, positive || i > 0, S);
        }
        if (smaller && positive) f[pos][s][mod] = res;
        return res;
    };
    auto solve = [&](long long x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        long long res = 0;
        for (int s = 1; s <= (int)a.size() * 9; ++s) {
            memset(f, -1, sizeof(f));
            res += dfs(a.size() - 1, s, 0, false, false, s);
        }
        return res;
    };
    long long l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

