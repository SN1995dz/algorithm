#include <bits/stdc++.h>

using namespace std;

// (S_ind+1)*2=T_ind
// (T_ind/2-1)=S_ind
// 2..2n: max_extend[i]-1;
// S[(i-max_extned[i])/2, (i+max_extned[i])/2-2]
vector<int> manacher(string s) {
    int n = s.length();
    string t = "$*";
    for (char c : s) {
        t += c;
        t += '*';
    }
    t += '#';
    int m = t.length();
    vector<int> max_extend(m, 0);
    max_extend[1] = 1;
    int j = 1;
    for (int i = 2; i <= 2 * n; ++i) {
        int cur_max_extend = j + max_extend[j] > i ? min(max_extend[j * 2 - i], j + max_extend[j] - i) : 1;
        while (t[i - cur_max_extend] == t[i + cur_max_extend]) ++cur_max_extend;
        if (i + cur_max_extend > j + max_extend[j]) j = i;
        max_extend[i] = cur_max_extend;
    }
    return max_extend;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string c, s;
    while (cin >> c >> s) {
        int d = c[0] - 'a';
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            s[i] = ((s[i] - 'a') + 26 - d) % 26 + 'a';
        }
        vector<int> m_e = manacher(s);
        int l = -1, r = -1;
        for (int i = 2; i <= 2 * n; ++i) {
            int nl = (i - m_e[i]) / 2, nr = (i + m_e[i]) / 2 - 2;
            if (l == -1 || (r - l + 1) < (nr - nl + 1)) {
                l = nl;
                r = nr;
            }
        }
        if (r - l + 1 >= 2) {
            cout << l << " " << r << endl;
            cout << s.substr(l, r - l + 1) << endl;
        } else {
            cout << "No solution!" << endl;
        }
    }
    return 0;
}

