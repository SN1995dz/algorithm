#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<int> b(m);
        for (int i = 0; i < m; ++i) cin >> b[i];
        sort(b.begin(), b.end());
        while (q--) {
            int a;
            cin >> a;
            int up = upper_bound(b.begin(), b.end(), a) - b.begin();
            if (up == 0) {
                cout << b[up] - 1 << endl;
                continue;
            }
            if (up == m) {
                cout << n - b[up - 1] << endl;
                continue;
            }
            cout << (b[up] - b[up - 1]) / 2 << endl;
        }
    }
    return 0;
}

