#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        long long d;
        int n, x;
        cin >> d >> n >> x;
        vector<long long> l(n);
        vector<int> q(n), v(n);
        vector<pair<long long, int>> a;
        for (int i = 0; i < n; ++i) {
            cin >> q[i] >> l[i] >> v[i];
            if (d - l[i] - 1 >= 0) a.push_back(make_pair(d - l[i] - 1, i));
        }
        a.push_back(make_pair(-1, -1));
        sort(a.rbegin(), a.rend());
        int m = a.size();
        priority_queue<pair<int, int>> pq;
        long long ans = 0;
        for (int l = 0, r = 0; l < m - 1; l = r) {
            while (a[r].first == a[l].first) {
                pq.push(make_pair(v[a[r].second], q[a[r].second]));
                ++r;
            }
            long long num = (a[l].first - a[r].first) * x;
            while (num && !pq.empty()) {
                auto e = pq.top();
                pq.pop();
                long long cnt = min(num, (long long)e.second);
                num -= cnt;
                e.second -= cnt;
                ans += cnt * e.first;
                if (e.second) pq.push(e);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

