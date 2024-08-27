#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (n >= 3) cout << "NO" << endl;
        else {
            if (a[1] == a[0] + 1) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
    }
    return 0;
}

