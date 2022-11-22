#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> a(6);
    const int w[6] = {1, 2, 3, 5, 10, 20};
    vector<bool> dp(1001, false);
    dp[0] = true;
    for (int i = 0; i < 6; ++i) cin >> a[i];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < a[i]; ++j) {
            for (int k = 1000; k >= w[i]; --k) {
                if (dp[k - w[i]] == true) dp[k] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000; ++i) ans += (dp[i] == true);
    cout << "Total=" << ans << endl;
    return 0;
}

