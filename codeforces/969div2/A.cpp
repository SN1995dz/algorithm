#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 < 3) {
            cout << 0 << endl;
            continue;
        }
        if (r - l + 1 == 3) {
            if (l % 2 == 0) cout << 0 << endl;
            else cout << 1 << endl;
            continue;
        }
        int n = r - l + 1;
        if (l % 2 == 0) --n;
        cout << (n + 1) / 4 << endl;
    }
    return 0;
}

