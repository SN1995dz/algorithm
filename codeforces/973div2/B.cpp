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
        long long sum = 0;
        for (int i = 0; i < n - 2; ++i) sum += a[i];
        cout << sum + a[n - 1] - a[n - 2] << endl;
    }
    return 0;
}

