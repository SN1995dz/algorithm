#include <iostream>
#include <vector>

using namespace std;

template<typename T>
vector<int> getP(const T& s) {
    int n = s.size();
    vector<int> P(n, -1);
    for (int i = 1, j = -1; i < n; ++i) {
        while (j >= 0 && s[j + 1] != s[i]) j = P[j];
        if (s[j + 1] == s[i]) ++j;
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
    while (true) {
        cin >> s;
        if (s[0] == '.') break;
        vector<int> P = getP(s);
        int n = s.length();
        int period = 1;
        if (n % (n - (P[n - 1] + 1)) == 0) period = n / (n - (P[n - 1] + 1));
        cout << period << endl;
    }
    return 0;
}

