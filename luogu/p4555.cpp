#include <bits/stdc++.h>

using namespace std;

// (S_ind+1)*2=T_ind
// (T_ind/2-1)=S_ind
// 2..2n: m_e[i]-1
// num: sum{m_e[i]/2}
// l=(i-m_e[i])/2, r=(i+m_e[i])/2-2
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
    string s;
    cin >> s;
    vector<int> m_e = manacher(s);
    int n = s.length();
    vector<int> L(n, 1), R(n, 1);
    for (int i = 2; i <= 2 * n; ++i) {
        int l = (i - m_e[i]) / 2, r = (i + m_e[i]) / 2 - 2;
        L[r] = max(L[r], r - l + 1);
        R[l] = max(R[l], r - l + 1);
    }
    for (int i = n - 2; i >= 0; --i) L[i] = max(L[i], L[i + 1] - 2);
    for (int i = 1; i < n; ++i) R[i] = max(R[i], R[i - 1] - 2);
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        ans = max(ans, L[i] + R[i + 1]);
    }
    cout << ans << endl;
    return 0;
}

