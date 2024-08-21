#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            --x;
            ++a[x];
        }
        int ans = n - 1;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, n - a[i]);
        }
        cout << ans << endl;
    }
    return 0;
}

