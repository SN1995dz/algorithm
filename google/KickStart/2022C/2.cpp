#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, L;
    cin >> n >> L;
    vector<int> p(n), d(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> d[i];
    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i + 1;
    sort(label.begin(), label.end(), [&](const int &i, const int &j) {
        return p[i - 1] < p[j - 1];
    });
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int tmp;
        if (d[i] == 0) tmp = p[i];
        else tmp = L - p[i];
        a.push_back(make_pair(tmp, d[i]));
    }
    sort(a.begin(), a.end());
    vector<pair<int, int>> ans;
    int l = 0, r = n - 1;
    for (int i = 0; i < n; ++i) {
        int who;
        if (a[i].second == 0) {
            who = label[l];
            ++l;
        } else {
            who = label[r];
            --r;
        }
        ans.push_back(make_pair(a[i].first, who));
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < n; ++i) {
        cout << ans[i].second << (i == n - 1 ? '\n' : ' ');
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

