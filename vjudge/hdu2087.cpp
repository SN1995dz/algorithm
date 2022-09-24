#include <bits/stdc++.h>

using namespace std;

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
    cin.tie(0);
    while (true) {
        string s;
        cin >> s;
        if (s.length() == 1 && s[0] == '#') break;
        string p;
        cin >> p;
        vector<int> ans = kmp(s, p);
        int last = -p.length();
        int cnt = 0;
        for (auto x : ans) {
            if (x >= last + (int)p.length()) {
                ++cnt;
                last = x;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}

