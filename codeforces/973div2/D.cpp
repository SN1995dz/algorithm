#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        stack<pair<long long, int>> S;
        S.push(make_pair(a[n - 1], 1));
        for (int i = n - 2; i >= 0; --i) {
            long long sum = a[i];
            int cnt = 1;
            while (!S.empty() && S.top().first <= (sum + cnt - 1) / cnt) {
                sum += S.top().first * S.top().second;
                cnt += S.top().second;
                S.pop();
            }
            int tmp = sum % cnt;
            if (tmp) S.push(make_pair(sum / cnt + 1, tmp));
            S.push(make_pair(sum / cnt, cnt - tmp));
        }
        long long mn = 1e13, mx = 0;
        while (!S.empty()) {
            mn = min(mn, S.top().first);
            mx = max(mx, S.top().first);
            S.pop();
        }
        cout << mx - mn << endl;
    }
    return 0;
}

