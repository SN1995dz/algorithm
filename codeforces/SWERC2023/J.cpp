#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, p;
    cin >> n >> p;
    vector<int> d(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        ++d[u], ++d[v];
    }
    int children = 0;
    for (int i = 0; i < n; ++i) {
        if (d[i] == 1) ++children;
    }
    if (n == 1) cout << 0 << endl;
    else if (n == 2) cout << p << endl;
    else {
        int ans = p / children * 2;
        ans += min(p % children, 2);
        cout << ans << endl;
    }
    return 0;
}

