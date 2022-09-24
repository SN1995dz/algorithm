#include <iostream>
#include <vector>

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
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> m;
        vector<string> s(m);
        for (int i = 0; i < m; ++i) {
            cin >> s[i];
        }
        string ans = "";
        int res = 0;
        for (int l = 0; l < 60; ++l) {
            for (int r = l; r < 60; ++r) {
                string p = s[0].substr(l, r - l + 1);
                bool flag = true;
                for (int i = 1; i < m; ++i) {
                    vector<int> res = kmp(s[i], p);
                    if (res.size() == 0) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    if (r - l + 1 > res) {
                        res = r - l + 1;
                        ans = p;
                    } else {
                        if (r - l + 1 == res && p < ans) {
                            ans = p;
                        }
                    }
                }
            }
        }
        if (ans.length() < 3) {
            cout << "no significant commonalities" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}

