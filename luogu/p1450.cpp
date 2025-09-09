#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> c(4);
    for (int i = 0; i < 4; ++i) cin >> c[i];
    int S = 1e5;
    vector<long long> f(S + 1, 0);
    f[0] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= S; ++j) {
            if (j - c[i] >= 0) f[j] += f[j - c[i]];
        }
    }
    int n;
    cin >> n;
    while (n--) {
        vector<int> d(4);
        int s;
        for (int i = 0; i < 4; ++i) cin >> d[i];
        cin >> s;
        long long ans = f[s];
        for (int mask = 1; mask < (1 << 4); ++mask) {
            int sign = 1;
            long long sum = 0;
            for (int i = 0; i < 4; ++i) {
                if (mask >> i & 1) {
                    sign *= -1;
                    sum += (long long)c[i] * (d[i] + 1);
                }
            }
            if (s - sum >= 0) {
                ans += sign * f[s - sum];
            }
        }
        cout << ans << endl;
    }
    return 0;
}

