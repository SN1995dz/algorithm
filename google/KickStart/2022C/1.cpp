#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    int sum = (1 + n) * n / 2;
    if (sum % (x + y) != 0) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    x = sum / (x + y) * x;
    int cur = n;
    vector<int> ans;
    while (x) {
        if (x >= cur) {
            x -= cur;
            ans.push_back(cur);
            --cur;
        } else {
            ans.push_back(x);
            cur = x - 1;
            x -= x;
        }
    }
    cout << "POSSIBLE" << endl;
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    }
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

