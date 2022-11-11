#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

void solve() {
    int r, a, b;
    cin >> r >> a >> b;
    double ans = 0.0;
    while (r) {
        ans += (double)r * r;
        r = r * a;
        ans += (double)r * r;
        r = r / b;
    }
    cout << fixed << setprecision(10) << ans * PI << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

