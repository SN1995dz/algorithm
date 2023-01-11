#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') ++a;
        else ++b;
    }
    int l = 1;
    for (int i = 0; i < a; ++i) {
        l *= 2;
    }
    int r = 1;
    for (int i = 0; i < b; ++i) {
        r *= 2;
    }
    r = (1 << n) - r + 1;
    for (int i = l; i <= r; ++i) {
        cout << i << " \n"[i == r];
    }
    return 0;
}

