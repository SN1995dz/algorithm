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
        map<int, int> M;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++M[x];
        }
        vector<pair<int, int>> a;
        for (auto &e : M) {
            a.push_back(make_pair(e.first, e.second));
        }
        if ((int)a.size() == 1) {
            cout << a[0].second / 2 << endl;
            continue;
        }
        sort(a.begin(), a.end());
        long long ans = 0, sum = 0;
        for (int i = 0; i < (int)a.size() - 1; ++i) {
            sum += a[i].second;
            ans = max(ans, sum * (n - sum));
        }
        cout << ans << endl;
    }
    return 0;
}

