#include <iostream>
#include <vector>
#include <algorithm>

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
    for (int i = 0, j = -1; i < (int)s.length(); ++i) {
        while (j >= 0 && p[j + 1] != s[i]) j = P[j];
        if (p[j + 1] == s[i]) ++j;
        if (j == (int)p.length() - 1) {
            res.push_back(i - j);
            j = P[j];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (cin >> s) {
        vector<int> P = getP(s);
        vector<int> ans;
        int j = s.length() - 1;
        while (j >= 0) {
            ans.push_back(j + 1);
            j = P[j];
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}

