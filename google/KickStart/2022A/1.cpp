#include <bits/stdc++.h>

using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = (sum + s[i] - '0') % 9;
    }
    string ans;
    if (sum == 0) {
        ans = s.substr(0, 1) + "0" + s.substr(1);
    } else {
        int d = 9 - sum;
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            if (s[i] - '0' > d) {
                ans = s.substr(0, i);
                ans.push_back(d + '0');
                ans += s.substr(i);
                flag = true;
                break;
            }
        }
        if (!flag) {
            ans = s;
            ans.push_back(d + '0');
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

