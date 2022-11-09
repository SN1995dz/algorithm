#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    bool a = false, b = false, c = false, d = false;
    for (int i = 0; i < n; ++i) {
        if (isupper(s[i])) a = true;
        if (islower(s[i])) b = true;
        if (isdigit(s[i])) c = true;
        if (s[i] == '#' || s[i] == '@' || s[i] == '*' || s[i] == '&') d = true;
    }
    if (a == false) s.push_back('A');
    if (b == false) s.push_back('a');
    if (c == false) s.push_back('0');
    if (d == false) s.push_back('#');
    while (s.length() < 7) s.push_back('0');
    cout << s << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

