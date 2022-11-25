#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long m;
    cin >> n >> m;
    vector<int> K(n), C(n);
    int W = 0;
    for (int i = 0; i < n; ++i) cin >> K[i];
    for (int i = 0; i < n; ++i) {
        cin >> C[i];
        W += C[i] * K[i];
    }
    vector<long long> f(1e6, 0);
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = W; j >= 1; --j) {
            for (int k = 1; k <= K[i] && k * C[i] <= j; ++k) {
                if (f[j - k * C[i]] * k >= m) f[j] = m;
                else f[j] = max(f[j], f[j - k * C[i]] * k);
            }
        }
    }
    int ans = 1;
    while (f[ans] < m) ++ans;
    cout << ans << endl;
    return 0;
}

