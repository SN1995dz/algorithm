#include <bits/stdc++.h>

using namespace std;

// p[i] = max{x}->a[0..x-1]=a[i-x+1..i]; len=p[i]+1
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

// @return starting positions of all matching strings in ascending order
template<typename T>
vector<int> kmp(const T& s, const T& p) {
    vector<int> res;
    vector<int> P = getP(p);
    for (int i = 0, j = -1; i < (int)s.size(); ++i) {
        while (j >= 0 && p[j + 1] != s[i]) j = P[j];
        if (p[j + 1] == s[i]) ++j;
        if (j == (int)p.size() - 1) {
            res.push_back(i - j);
            j = P[j];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];
    if (n < m) {
        cout << 0 << endl;
    } else if (m == 1) {
        cout << n << endl;
    } else {
        vector<int> c(n - 1);
        for (int i = 1; i < n; ++i) c[i - 1] = a[i - 1] - a[i];
        vector<int> d(m - 1);
        for (int i = 1; i < m; ++i) d[i - 1] = b[i - 1] - b[i];
        vector<int> ans = kmp(c, d);
        cout << ans.size() << endl;
    }
    return 0;
}

