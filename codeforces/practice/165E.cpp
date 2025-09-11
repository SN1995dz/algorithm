#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int maxVal = *max_element(a.begin(), a.end());
    int B = 0;
    while (maxVal) {
        ++B;
        maxVal >>= 1;
    }
    vector<int> f(1 << B, -1);
    for (int i = 0; i < n; ++i) {
        f[a[i]] = a[i];
    }
    for (int mask = 1; mask < (1 << B); ++mask) {
        for (int i = 0; i < B; ++i) {
            if (mask >> i & 1 && f[mask ^ (1 << i)] != -1) {
                f[mask] = f[mask ^ (1 << i)];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << f[((1 << B) - 1) ^ a[i]] << " ";
    }
    cout << endl;
    return 0;
}

