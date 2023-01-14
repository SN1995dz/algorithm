#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(m);
        for (int i = 0; i < m; ++i) {
            cin >> a[i];
        }
        sort(a.rbegin(), a.rend());
        bool ans = true;
        if ((n - 1) / k + 1 < a[0]) ans = false;
        if (ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

