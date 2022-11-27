#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
        }
        if (a[0] >= k) {
            cout << "YES" << endl;
            continue;
        }
        if (a[0] < k - b[0]) {
            cout << "NO" << endl;
            continue;
        }
        long long cur = k - b[0];
        vector<pair<int, int>> c;
        for (int i = 1; i < n; ++i) {
            c.push_back(make_pair(a[i] + b[i], a[i]));
        }
        sort(c.rbegin(), c.rend());
        int j = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        while (j < (int)c.size() && c[j].first >= cur) {
            pq.push(make_pair(c[j].second - (c[j].first - c[j].second), c[j].second));
            ++j;
        }
        bool ok = false;
        while (!pq.empty()) {
            auto e = pq.top();
            pq.pop();
            if (e.second >= cur) {
                ok = true;
                break;
            }
            int B = e.second - e.first;
            cur -= B;
            while (j < (int)c.size() && c[j].first >= cur) {
                pq.push(make_pair(c[j].second - (c[j].first - c[j].second), c[j].second));
                ++j;
            }
        }
        if (ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

