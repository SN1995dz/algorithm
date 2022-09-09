#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    int offset = 1600;
    vector<vector<vector<long long>>> f(19, vector<vector<long long>>(19, vector<long long>(3201, -1)));
    function<long long(int, int, int, bool, bool)> dfs = [&](int pos, int p, int diff, bool smaller, bool positive) {
        if (pos < 0) {
            if (diff == 0 && positive) return 1LL;
            return 0LL;
        }
        if (smaller && positive && f[pos][p][diff + offset] != -1) return f[pos][p][diff + offset];
        long long res = 0;
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            res += dfs(pos - 1, p, diff + (p - pos) * i, smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][p][diff + offset] = res;
        return res;
    };
    auto solve = [&](long long x) {
        if (x < 0) return 0LL;
        if (x == 0) return 1LL;
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        long long res = 0;
        for (int p = 0; p < (int)a.size(); ++p) {
            res += dfs(a.size() - 1, p, 0, false, false);
        }
        return res + 1;
    };
    int T;
    cin >> T;
    while (T--) {
        long long l, r;
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}

