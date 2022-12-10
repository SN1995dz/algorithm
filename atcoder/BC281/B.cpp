#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    auto check = [&](string s) {
        if (s.length() != 8) return false;
        if (s[0] < 'A' || s[0] > 'Z') return false;
        if (s.back() < 'A' || s.back() > 'Z') return false;
        if (s[1] < '1' || s[1] > '9') return false;
        for (int i = 2; i < 7; ++i) {
            if (s[i] < '0' || s[i] > '9') return false;
        }
        return true;
    };
    string s;
    cin >> s;
    if (check(s)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}

