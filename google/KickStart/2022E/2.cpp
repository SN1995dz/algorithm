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

bool check(int l, int r, vector<int>& m_e) {
    int ll = (l + 1) * 2, rr = (r + 1) * 2;
    int mid = (ll + rr) / 2;
    if (m_e[mid] - 1 >= r - l + 1) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> m_e = manacher(s);
        int res = n;
        for (int i = 1; i < n; ++i) {
            if (check(0, i - 1, m_e) && check(i, n - 1, m_e)) {
                res = i;
                break;
            }
        }
        string ans = s.substr(0, res);
        cout << ans << endl;
    }
    return 0;
}

