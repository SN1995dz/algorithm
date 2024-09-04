#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int x = 0;
        for (int i = 0; i < n; ++i) {
            int y;
            cin >> y;
            x = max(x, y);
        }
        while (m--) {
            string op;
            int l, r;
            cin >> op >> l >> r;
            if (l <= x && x <= r) {
                if (op[0] == '+') ++x;
                else --x;
            }
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}

