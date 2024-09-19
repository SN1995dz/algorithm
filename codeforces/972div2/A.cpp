#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    string vow = "aeiou";
    while (T--) {
        int n;
        cin >> n;
        string ans = "";
        for (int i = 0; i < n; ++i) {
            ans.push_back(vow[i % 5]);
        }
        sort(ans.begin(), ans.end());
        cout << ans << endl;
    }
    return 0;
}

