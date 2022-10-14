#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int n;
        cin >> n;
        vector<pair<string, int>> a;
        vector<pair<int, int>> b;
        for (int i = 0; i < n; ++i) {
            string c;
            int d, u;
            cin >> c >> d >> u;
            a.push_back(make_pair(c, u));
            b.push_back(make_pair(d, u));
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i].second == b[i].second) ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}

