#include <bits/stdc++.h>

using namespace std;

long long f[11][11][11][2][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    function<long long(int, int, int, bool, int, bool, bool)> dfs = [&](int pos, int pp, int p, bool tri, int mask, bool smaller, bool positive) {
        if (pos < 0) {
            if (tri == true && mask != 3) {
                return 1LL;
            }
            return 0LL;
        }
        if (smaller && positive && f[pos][pp + 1][p + 1][tri][mask] != -1) return f[pos][pp + 1][p + 1][tri][mask];
        long long res = 0;
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            if (pos == (int)a.size() - 1 && i == 0) continue;
            int nmask = mask;
            if (i == 4 || i == 8) {
                nmask = nmask | (i / 4);
            }
            bool ntri = tri;
            if (i == p && i == pp) {
                ntri = true;
            }
            res += dfs(pos - 1, p, i, ntri, nmask, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][pp + 1][p + 1][tri][mask] = res;
        return res;
    };
    auto solve = [&](long long x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        if (a.size() != 11) a.push_back(0);
        return dfs(a.size() - 1, -1, -1, false, 0, false, false);
    };
    long long l, r;
    cin >> l >> r;
    memset(f, -1, sizeof(f));
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

