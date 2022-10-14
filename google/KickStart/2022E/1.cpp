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
        vector<int> r(n);
        multiset<int> MS;
        for (int i = 0; i < n; ++i) {
            cin >> r[i];
            MS.insert(r[i]);
        }
        vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i) {
            MS.erase(MS.find(r[i]));
            auto it = MS.upper_bound(2 * r[i]);
            if (it != MS.begin()) {
                --it;
                ans[i] = *it;
            }
            MS.insert(r[i]);
        }
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

