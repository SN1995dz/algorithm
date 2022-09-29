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
//template<typename T>
//vector<int> kmp(const T& s, const T& p) {
//    vector<int> res;
//    vector<int> P = getP(p);
//    for (int i = 0, j = -1; i < (int)s.size(); ++i) {
//        while (j >= 0 && p[j + 1] != s[i]) j = P[j];
//        if (p[j + 1] == s[i]) ++j;
//        if (j == (int)p.size() - 1) {
//            res.push_back(i - j);
//            j = P[j];
//        }
//    }
//    return res;
//}

char s[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    //cin >> T;
    scanf("%d", &T);
    while (T--) {
        //string s;
        //cin >> s;
        scanf("%s", s);
        //int n = s.length();
        int n = strlen(s);
        //vector<int> P = getP(s);
        vector<int> P(n, -1);
        for (int i = 1, j = -1; i < n; ++i) {
            while (j >= 0 && s[j + 1] != s[i]) j = P[j];
            if (s[j + 1] == s[i]) ++j;
            P[i] = j;
        }
        int tmp = n - (P[n - 1] + 1);
        if (tmp == n) cout << n << endl;
        else cout << (tmp - n % tmp) % tmp << endl;
    }
    return 0;
}
