#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    stack<pair<int, int>> S;
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        while (!S.empty() && S.top().first < h[i]) S.pop();
        if (S.empty()) {
            ans += n - i - 1; 
        } else {
            ans += S.top().second - i - 1;
        }
        S.push(make_pair(h[i], i));
    }
    cout << ans << endl;
    return 0;
}

