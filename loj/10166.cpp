#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    int N;
    vector<vector<int>> f;
    function<int(int, int, bool, bool)> dfs = [&](int pos, int mod, bool smaller, bool positive) {
        if (pos < 0) return (int)(mod == 0);
        if (smaller && positive && f[pos][mod] != -1) return f[pos][mod];
        int res = 0, up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            res += dfs(pos - 1, (mod + i) % N, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][mod] = res;
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
    while (cin >> l >> r >> N) {
        f = vector<vector<int>>(11, vector<int>(N, -1));
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}

