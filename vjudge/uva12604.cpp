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
    int T;
    cin >> T;
    while (T--) {
        string a;
        cin >> a;
        int n = a.length();
        map<char, int> M;
        for (int i = 0; i < n; ++i) {
            M[a[i]] = i;
        }
        string p, s;
        cin >> p;
        cin >> s;
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            string tp;
            for (int j = 0; j < (int)p.length(); ++j) {
                tp.push_back(a[(M[p[j]] + i) % n]);
            }
            vector<int> res = kmp(s, tp);
            if (res.size() == 1) {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0) cout << "no solution" << endl;
        else if (ans.size() == 1) {
            cout << "unique: ";
            cout << ans[0] << endl;
        } else {
            cout << "ambiguous:";
            for (auto x : ans) {
                cout << " " << x;
            }
            cout << endl;
        }
    }
    return 0;
}

