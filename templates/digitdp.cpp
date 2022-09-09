#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    function<int(int, ..., bool, bool)> dfs = [&](int pos, ..., bool smaller, bool positive) {
        if (pos < 0) return ...; //1 or smaller && positive
        if (smaller && positive && f[pos][...] != -1) return f[pos][...];
        int res = 0, up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            res += dfs(pos - 1, ..., smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][...] = res;
        return res;
    };
    auto solve = [&](int x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        return dfs(a.size() - 1, ..., false, false);
    };
    int l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

