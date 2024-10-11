#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());
    const int INF = 1e9;
    int ans = INF;
    deque<pair<int, int>> maxDeq, minDeq;
    for (int i = 0; i < n; ++i) {
        while (!maxDeq.empty() && maxDeq.back().first <= a[i].second) maxDeq.pop_back();
        maxDeq.push_back(make_pair(a[i].second, a[i].first));
        while (!minDeq.empty() && minDeq.back().first >= a[i].second) minDeq.pop_back();
        minDeq.push_back(make_pair(a[i].second, a[i].first));
        while (maxDeq.front().first - minDeq.front().first >= d) {
            int L = min(maxDeq.front().second, minDeq.front().second);
            ans = min(ans, a[i].first - L);
            if (maxDeq.front().second <= L) maxDeq.pop_front();
            if (minDeq.front().second <= L) minDeq.pop_front();
        }
    }
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}

