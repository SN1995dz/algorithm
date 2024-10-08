#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    stack<pair<int, int>> S;
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; --i) {
        while (!S.empty() && S.top().first <= a[i]) S.pop();
        if (S.empty()) ans[i] = 0;
        else ans[i] = S.top().second + 1;
        S.push(make_pair(a[i], i));
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    return 0;
}

