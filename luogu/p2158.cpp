#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> f(n, 0);
    for (int i = n - 1; i >= 1; --i) {
        f[i] = ((n - 1) / i) * ((n - 1) / i);
        for (int j = i + i; j < n; j += i) f[i] -= f[j];
    }
    if (n == 1) cout << 0 << endl;
    else cout << f[1] + 2 << endl;
    return 0;
}

