#include <bits/stdc++.h>

using namespace std;

// z[i] = max{x}->a[0..x-1]=a[i..i+x-1]
template<typename T>
vector<int> z_algorithm(const T& a) {
    int n = a.size();
    vector<int> z(n);
    z[0] = n;
    int l = -1, r = -1;
    for (int i = 1; i < n; ++i) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < n && a[i + z[i]] == a[z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const int MOD = 10007;
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> z = z_algorithm(s);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = (ans + z[i]) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}

