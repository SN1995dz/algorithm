#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, a, b;
        cin >> n >> a >> b;
        a = __gcd(a, b);
        vector<int> c;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            c.push_back(t % a);
        }
        sort(c.begin(), c.end());
        int ans = c[n - 1] - c[0];
        for (int i = 0; i < n - 1; ++i) {
            ans = min(ans, c[i] + a - c[i + 1]);
        }
        cout << ans << endl;
    }
    return 0;
}

