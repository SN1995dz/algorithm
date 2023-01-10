#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        set<int> a, b;
        for (int i = 0; i < 3; ++i) {
            int x, y;
            cin >> x >> y;
            a.insert(x);
            b.insert(y);
        }
        if (a.size() == 3 || b.size() == 3) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

