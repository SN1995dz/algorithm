#include <bits/stdc++.h>
 
using namespace std;

int f[35][2][2][2];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const int MOD = 1e9 + 7;
    vector<int> a, b;
    int ans;
    function<int(int, bool, bool, bool)> dfs = [&](int pos, bool asmaller, bool bsmaller, bool positive) {
        if (pos < 0) return (int)positive;
        if (f[pos][asmaller][bsmaller][positive] != -1) return f[pos][asmaller][bsmaller][positive];
        int res = 0, aup = asmaller ? 1 : a[pos], bup = bsmaller ? 1 : b[pos];
        for (int i = 0; i <= aup; ++i) {
            for (int j = 0; j <= bup; ++j) {
                if (i == 1 && j == 1) continue;
                int tmp = dfs(pos - 1, asmaller || i < aup, bsmaller || j < bup, positive || i > 0 || j > 0);
                if (!positive && (i == 1 || j == 1)) ans = (ans + (long long)tmp * (pos + 1) % MOD) % MOD;
                res = (res + tmp) % MOD;
            }
        }
        return f[pos][asmaller][bsmaller][positive] = res;
    };
    auto solve = [&](int x, int y) {
        a.clear();
        b.clear();
        ans = 0;
        while (x || y) {
            a.push_back(x & 1);
            b.push_back(y & 1);
            x >>= 1;
            y >>= 1;
        }
        return dfs(a.size() - 1, false, false, false);
    };
    int T;
    cin >> T;
    while (T--) {
        memset(f, -1, sizeof(f));
        int x, y;
        cin >> x >> y;
        solve(x, y);
        cout << ans << endl;
    }
    return 0;
}
