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
        int x, y;
        cin >> x >> y;
        if (n % min(x, y) == 0) cout << n / min(x, y) << endl;
        else cout << n / min(x, y) + 1 << endl;
    }
    return 0;
}

