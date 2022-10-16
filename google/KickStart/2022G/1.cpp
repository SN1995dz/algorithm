#include <bits/stdc++.h>

using namespace std;

void solve() {
    int Rs, Rh;
    cin >> Rs >> Rh;
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.push_back(make_pair(x * x + y * y, 0));
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        a.push_back(make_pair(x * x + y * y, 1));
    }
    if (n == 0 && m == 0) {
        cout << "0 0" << endl;
        return;
    }
    sort(a.begin(), a.end());
    int w = -1;
    if (a[0].first <= (Rs + Rh) * (Rs + Rh)) {
        w = a[0].second;
    }
    if (w == -1) {
        cout << "0 0" << endl;
        return;
    }
    vector<int> ans(2, 0);
    ans[w] = 1;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i].first > (Rs + Rh) * (Rs + Rh)) {
            break;
        }
        if (a[i].second != w) break;
        ++ans[w];
    }
    cout << ans[0] << " " << ans[1] << endl;
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

