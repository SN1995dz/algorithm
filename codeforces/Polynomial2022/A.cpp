#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int sum = (s[0] == '1');
        string ans = "";
        for (int i = 1; i < n; ++i) {
            if (s[i] == '0') {
                ans.push_back('+');
            } else {
                if (sum == 0) {
                    ans.push_back('+');
                    ++sum;
                } else {
                    ans.push_back('-');
                    --sum;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}

