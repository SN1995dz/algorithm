#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (n < 5) {
        cout << "POSSIBLE" << endl;
        return;
    }
    auto check = [&](int mask, int len) {
        for (int i = 0, j = len - 1; i < j; ++i, --j) {
            if ((mask >> i & 1) != (mask >> j & 1)) return false;
        }
        return true;
    };
    vector f(n, vector<bool>(1 << 5, false));
    for (int mask = 0; mask < (1 << 5); ++mask) {
        if (check(mask, 5)) continue;
        bool flag = true;
        for (int i = 0; i < 5; ++i) {
            if (s[i] == '?') continue;
            if (s[i] == '1' && (mask >> (4 - i) & 1) == 0) {
                flag = false;
                break;
            }
            if (s[i] == '0' && (mask >> (4 - i) & 1) == 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            f[4][mask] = true;
        }
    }
    for (int i = 4; i < n - 1; ++i) {
        for (int mask = 0; mask < (1 << 5); ++mask) {
            if (f[i][mask] == false) continue;
            if (s[i + 1] == '?') {
                int nmask = mask << 1;
                if (check(nmask, 6) == false && check(nmask % 32, 5) == false) {
                    f[i + 1][nmask % 32] = true;
                }
                nmask += 1;
                if (check(nmask, 6) == false && check(nmask % 32, 5) == false) {
                    f[i + 1][nmask % 32] = true;
                }
            } else {
                int nmask = (mask << 1) + s[i + 1] - '0';
                if (check(nmask, 6) == false && check(nmask % 32, 5) == false) {
                    f[i + 1][nmask % 32] = true;
                }
            }
        }
    }
    bool ans = false;
    for (int mask = 0; mask < (1 << 5); ++mask) {
        if (f[n - 1][mask]) {
            ans = true;
            break;
        }
    }
    if (ans) cout << "POSSIBLE" << endl;
    else cout << "IMPOSSIBLE" << endl;
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

