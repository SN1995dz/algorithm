#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    vector<vector<int>> f(11, vector<int>(10, -1));
    function<int(int, int, bool, bool)> dfs = [&](int pos, int pre, bool smaller, bool positive) {
        if (pos < 0) return 1;
        if (smaller && positive && f[pos][pre] != -1) return f[pos][pre];
        int res = 0, up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            if (i < pre) continue;
            res += dfs(pos - 1, i, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][pre] = res;
        return res;
    };
    auto solve = [&](int x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        return dfs(a.size() - 1, 0, false, false);
    };
    int l, r;
    while (cin >> l >> r) {
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}

