#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i + 2 < n; ++i) {
        if (s[i + 1] == '.' && s[i] == '#' && s[i + 2] == '#') ++ans;
    }
    cout << ans << endl;
    return 0;
}

