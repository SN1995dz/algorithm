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

vector<vector<int>> computeAutomation(string s) {
    int n = s.length();
    vector<int> P = getP(s);
    vector<vector<int>> aut(n + 1, vector<int>(26));
    for (int i = 0; i <= n; ++i) {
        for (int c = 0; c < 26; ++c) {
            if (i == n || (i > 0 && 'a' + c != s[i])) aut[i][c] = aut[P[i - 1] + 1][c];
            else aut[i][c] = i + ('a' + c == s[i]);
        }
    }
    return aut;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, p;
    cin >> s >> p;
    int n = s.length(), m = p.length();
    vector<vector<int>> nxt = computeAutomation(p);
    vector<vector<int>> f(n + 1, vector<int>(m + 1, -1));
    f[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (f[i][j] == -1) continue;
            if (s[i] == '?') {
                for (int c = 0; c < 26; ++c) {
                    int t = nxt[j][c];
                    f[i + 1][t] = max(f[i + 1][t], f[i][j] + (t == m));
                }
            } else {
                int t = nxt[j][s[i] - 'a'];
                f[i + 1][t] = max(f[i + 1][t], f[i][j] + (t == m));
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= m; ++j) ans = max(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}

