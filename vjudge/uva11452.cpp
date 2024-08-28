#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.length();
        for (int i = 1; i <= n; ++i) {
            if (i * 2 > n) break;
            if (i * 3 <= n) continue;
            bool flag = true;
            for (int j = 0; j < i; ++j) {
                if (s[j] != s[j + i]) {
                    flag = false;
                    break;
                }
            }
            for (int j = 0; j < i && j + i + i < n; ++j) {
                if (s[j] != s[j + i + i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                int tmp = n - i * 2;
                for (int j = 0; j < 8; ++j) {
                    cout << s[(tmp + j) % i];
                }
                cout << "..." << endl;
                break;
            }
        }
    }
    return 0;
}

