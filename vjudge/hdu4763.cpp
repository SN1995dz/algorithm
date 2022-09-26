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

// p[i] = max{x}->a[0..x-1]=a[i-x+1..i]
template<typename T>
vector<int> getP(const T& a) {
    int n = a.size();
    vector<int> P(n, -1);
    for (int i = 1, j = -1; i < n; ++i) {
        while (j >= 0 && a[j + 1] != a[i]) j = P[j];
        if (a[j + 1] == a[i]) ++j;
        P[i] = j;
    }
    return P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.length();
        vector<int> z = z_algorithm(s);
        vector<int> P = getP(s);
        //int len = P[n - 1] + 1;
        int j = n - 1;
        //while ((P[j] + 1) * 3 > n) j = P[j];
        int ans = 0;
        int l = -1, r = -1;
        int mx = 0;
        while (P[j] + 1 > 0) {
            if ((P[j] + 1) * 3 <= n) {
                int len = P[j] + 1;
                int nl = len, nr = n - len * 2;
                if (l == -1 && r == -1) {
                    for (int i = nl; i <= nr; ++i) {
                        mx = max(mx, z[i]);
                    }
                } else {
                    for (int i = nl; i < l; ++i) {
                        mx = max(mx, z[i]);
                    }
                    for (int i = r + 1; i <= nr; ++i) {
                        mx = max(mx, z[i]);
                    }
                }
                l = nl, r = nr;
                if (mx >= len) {
                    ans = len;
                    break;
                }
            }
            j = P[j];
        }
        cout << ans << endl;
    }
    return 0;
}

