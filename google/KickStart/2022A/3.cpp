#include <bits/stdc++.h>

using namespace std;

long long f[13][108][109];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        vector<int> a;
        function<long long(int, int, int, bool, bool, int)> dfs = [&](int pos, int pow, int sum, bool smaller, bool positive, int MOD) {
            if (pos < 0) return (long long)(pow == 0 && sum == MOD);
            if (smaller && positive && f[pos][pow][sum] != -1) return f[pos][pow][sum];
            long long res = 0;
            int up = smaller ? 9 : a[pos];
            for (int i = 0; i <= up; ++i) {
                if (sum + i > MOD) break;
                if (i == 0 && !positive) res += dfs(pos - 1, pow, sum, smaller || i < up, positive || i > 0, MOD);
                else res += dfs(pos - 1, pow * i % MOD, sum + i, smaller || i < up, positive || i > 0, MOD);
            }
            if (smaller && positive) f[pos][pow][sum] = res;
            return res;
        };
        auto solve = [&](long long x) {
            a.clear();
            int n = 0;
            while (x) {
                a.push_back(x % 10);
                ++n;
                x /= 10;
            }
            long long res = 0;
            for (int i = 1; i <= min(n * 9, 108); ++i) {
                memset(f, -1, sizeof(f));
                res += dfs(a.size() - 1, 1 % i, 0, false, false, i); 
            }
            return res;
        };
        long long l, r;
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}

