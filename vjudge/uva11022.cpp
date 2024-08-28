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
    while (true) {
        string s;
        cin >> s;
        if (s.length() == 1 && s[0] == '*') break;
        int n = s.length();
        vector<vector<int>> f(n, vector<int>(n, -1));
        function<int(int, int)> solve = [&](int l, int r) {
            if (f[l][r] != -1) return f[l][r];
            if (l == r) return 1;
            int len = r - l + 1;
            int res = len;
            vector<int> p = getP(s.substr(l, len));
            if (p[len - 1] != -1 && len % (len - (p[len - 1] + 1)) == 0) {
                res = min(res, solve(l, l + len - (p[len - 1] + 1) - 1));
            }
            for (int i = l; i < r; ++i) {
                res = min(res, solve(l, i) + solve(i + 1, r));
            }
            return f[l][r] = res;
        };
        cout << solve(0, n - 1) << endl;
    }
    return 0;
}

