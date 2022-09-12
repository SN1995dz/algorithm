#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    int k, b;
    vector<vector<int>> f(32, vector<int>(21, -1));
    function<int(int, int, bool, bool)> dfs = [&](int pos, int cnt, bool smaller, bool positive) {
        if (pos < 0) return (int)(cnt == k);
        if (smaller && positive && f[pos][cnt] != -1) return f[pos][cnt];
        int res = 0, up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            if (i > 1) break;
            if (cnt + (i == 1) > k) break;
            res += dfs(pos - 1, cnt + (i == 1), smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][cnt] = res;
        return res;
    };
    auto solve = [&](int x) {
        a.clear();
        while (x) {
            a.push_back(x % b);
            x /= b;
        }
        return dfs(a.size() - 1, 0, false, false);
    };
    int l, r;
    cin >> l >> r;
    cin >> k >> b;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

