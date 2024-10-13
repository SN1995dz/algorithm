#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    x.push_back(0);
    y.push_back(0);
    int sx = 0, sy = 0;
    long double ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += sqrt((long long)(x[i] - sx) * (x[i] - sx) + (long long)(y[i] - sy) * (y[i] - sy));
        sx = x[i], sy = y[i];
    }
    cout << fixed << setprecision(8) << ans << endl;
    return 0;
}

