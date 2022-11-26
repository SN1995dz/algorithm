#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, x;
        cin >> n >> x;
        if (n % x != 0) {
            cout << -1 << endl;
            continue;
        }
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) p[i] = i;
        p[n] = 1;
        p[1] = x;
        int cur = x;
        while (cur != n) {
            bool flag = false;
            for (int i = 2; ; ++i) {
                if (i * cur >= n) {
                    flag = true;
                    break;
                }
                if (n % (i * cur) == 0) {
                    p[cur] = i * cur;
                    cur = i * cur;
                    break;
                }
            }
            if (flag) {
                p[cur] = n;
                break;
            }
        }
        for (int i = 1; i <= n; ++i) {
            cout << p[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}

