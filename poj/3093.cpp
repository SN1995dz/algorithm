#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ++ca) {
        int n, W;
        cin >> n >> W;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.rbegin(), a.rend());
        if (a.back() > W) {
            cout << ca << " " << 0 << endl;
            continue;
        }
        vector<vector<int> > f(n + 1, vector<int>(W + 1, 0));
        f[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= W; ++j) {
                f[i + 1][j] = f[i][j];
                if (j - a[i] >= 0) f[i + 1][j] += f[i][j - a[i]];
            }
        }
        int ans = 0;
        int sum = 0;
        for (int i = n - 1; i >= 0; --i) {
            int C = W - sum;
            for (int j = C; C - j < a[i] && j >= 0; --j) {
                ans += f[i][j];
            }
            sum += a[i];
            if (sum > W) break;
        }
        if (sum <= W) ++ans;
        cout << ca << " " << ans << endl;
    }
    return 0;
}

