#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n), v(n);
    for (int i = 0; i < n; ++i) cin >> h[i] >> v[i];
    vector<int> ans(n, 0);
    stack<pair<int, int>> S;
    for (int i = n - 1; i >= 0; --i) {
        while (!S.empty() && S.top().first <= h[i]) S.pop();
        if (!S.empty()) {
            ans[S.top().second] += v[i];
        }
        S.push(make_pair(h[i], i));
    }
    while (!S.empty()) S.pop();
    for (int i = 0; i < n; ++i) {
        while (!S.empty() && S.top().first <= h[i]) S.pop();
        if (!S.empty()) {
            ans[S.top().second] += v[i];
        }
        S.push(make_pair(h[i], i));
    }
    int res = 0;
    for (int i = 0; i < n; ++i) res = max(res, ans[i]);
    cout << res << endl;
    return 0;
}

