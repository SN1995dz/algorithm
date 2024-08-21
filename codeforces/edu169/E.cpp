#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int N = 1e7, MAX = 1e9;
    vector<int> sg(N + 1, MAX);
    sg[1] = 1;
    int cnt = 2;
    for (int i = 3; (long long)i <= N; i += 2) {
        if (sg[i] == MAX) {
            sg[i] = cnt++;
        } else {
            continue;
        }
        if ((long long)i * i > N) continue;
        for (int j = i * 3; j <= N; j += i + i) {
            sg[j] = min(sg[j], sg[i]);
        }
    }
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x % 2 == 0) res ^= 0;
            else res ^= sg[x];
        }
        if (res == 0) cout << "Bob" << endl;
        else cout << "Alice" << endl;
    }
    return 0;
}

