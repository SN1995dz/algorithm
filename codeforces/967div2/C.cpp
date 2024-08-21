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
        vector<vector<bool>> G(n, vector<bool>(n, false));
        vector<bool> flag(n, false);
        flag[0] = true;
        function<void(int, int)> connect = [&](int a, int b) {
            if (flag[b]) return;
            cout << "? " << a + 1 << " " << b + 1 << endl;
            cout.flush();
            int x;
            cin >> x;
            --x;
            if (x == a) {
                G[a][b] = true;
                G[b][a] = true;
                flag[b] = true;
                return;
            }
            connect(a, x);
            connect(x, b);
        };
        for (int i = 1; i < n; ++i) {
            if (flag[i] == false) {
                connect(0, i);
            }
        }
        cout << "!";
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (G[i][j] == true) {
                    cout << " " << i + 1 << " " << j + 1;
                }
            }
        }
        cout << endl;
        cout.flush();
    }
    return 0;
}

