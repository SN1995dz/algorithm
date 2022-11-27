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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        int g = __gcd(a[0], a[1]);
        for (int i = 2; i < n; ++i) g = __gcd(g, a[i]);
        cout << a[n - 1] / g << endl;
    }
    return 0;
}

