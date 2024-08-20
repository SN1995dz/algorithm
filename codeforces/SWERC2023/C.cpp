#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    bool flag = true;
    set<int> S;
    vector<long long> a(n);
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        int tmp = 0;
        for (int j = 0; j < k; ++j) {
            int c;
            cin >> c;
            tmp |= 1 << c;
            a[c] |= 1LL << i;
        }
        if (S.count(tmp)) {
            flag = false;
        }
        S.insert(tmp);
    }
    if (flag == false) {
        cout << "not possible" << endl;
        return 0;
    }
    map<long long, double> M;
    function<double(long long)> solve = [&](long long state) {
        if (__builtin_popcountll(state) == 1) return 0.0;
        if (M.count(state)) return M[state];
        double res = n;
        for (int i = 0; i < n; ++i) {
            long long X = a[i] & state;
            long long Y = X ^ state;
            if (X == 0 || Y == 0) continue;
            res = min(res, (solve(X) * __builtin_popcountll(X) + solve(Y) * __builtin_popcountll(Y)) / __builtin_popcountll(state) + 1.0);
        }
        return M[state] = res;
    };
    cout << fixed << setprecision(5) << solve((1LL << m) - 1) << endl;
    return 0;
}

