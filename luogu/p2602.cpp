#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<long long> a;
    vector<vector<long long>> f(13, vector<long long>(1 << 13, -1));
    function<long long(int, int, int, bool, bool)> dfs = [&](int pos, int mask, int d, bool smaller, bool positive) {
        long long res = 0;
        if (pos < 0) {
            for (int i = 0; i < 13; ++i) {
                if (mask >> i & 1) ++res;
            }
            return res;
        }
        if (smaller && positive && f[pos][mask] != -1) return f[pos][mask];
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            int nmask = mask;
            if (i == d) {
                if (i == 0) {
                    if (positive) nmask |= (1 << pos);
                } else {
                    nmask |= (1 << pos);
                }
            }
            res += dfs(pos - 1, nmask, d, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][mask] = res;
        return res;
    };
    auto solve = [&](long long l, long long r, int d) {
        a.clear();
        while (r) {
            a.push_back(r % 10);
            r /= 10;
        }
        long long ans = 0;
        ans += dfs(a.size() - 1, 0, d, false, false);
        a.clear();
        --l;
        while (l) {
            a.push_back(l % 10);
            l /= 10;
        }
        ans -= dfs(a.size() - 1, 0, d, false, false);
        return ans;
    };
    long long l, r;
    cin >> l >> r;
    for (int i = 0; i < 10; ++i) cout << solve(l, r, i) << " ";
    cout << endl;
    return 0;
}

