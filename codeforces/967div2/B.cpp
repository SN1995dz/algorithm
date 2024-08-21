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
        if (n % 2 == 0) {
            cout << -1 << endl;
        } else {
            for (int i = n; i >= 1; i -= 2) cout << i << " ";
            for (int i = 2; i < n; i += 2) cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}

