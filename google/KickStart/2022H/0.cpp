#include <bits/stdc++.h>

using namespace std;

void solve() {
    int L, N;
    cin >> L >> N;
    int D = 0;
    string C;
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        int d;
        string c;
        cin >> d >> c;
        if (D == 0) {
            C = c;
        }
        if (c[0] == 'C') {
            if (c == C) {
                ans += (D + d) / L;
            } else {
                ans += max(0, (D + d) / L - 1);
            }
            if ((D + d) / L) C = c;
            D = (D + d) % L;
        } else {
            D = (L - D) % L;
            if (c == C) {
                ans += (D + d) / L;
            } else {
                ans += max(0, (D + d) / L - 1);
            }
            if ((D + d) / L) C = c;
            D = (D + d) % L;
            D = (L - D) % L;
        }
    }
    cout << ans << endl;
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

