#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        for (int i = s.length() - 1; i >= 0; --i) s.push_back(s[i]);
        cout << s << endl;
    }
    return 0;
}

