#include <iostream>
#include <vector>

using namespace std;

// (S_ind+1)*2=T_ind
// (T_ind/2-1)=S_ind
// 2..2n: max_extend[i]-1;
// S[(i-max_extned[i])/2, (i+max_extned[i])/2-2]
vector<int> manacher(string s) {
    int n = s.length();
    string t = "$*";
    for (int i = 0; i < n; ++i) {
        t += s[i];
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
    int Case = 0;
    while (true) {
        string s;
        cin >> s;
        if (s == "END") break;
        ++Case;
        cout << "Case " << Case << ": ";
        int n = s.length();
        vector<int> m_e = manacher(s);
        int ans = 0;
        for (int i = 2; i <= 2 * n; ++i) {
            ans = max(ans, m_e[i] - 1);
        }
        cout << ans << endl;
    }
    return 0;
}

