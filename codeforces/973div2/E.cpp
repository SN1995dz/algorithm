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
        vector<int> a(n);
        set<int> S;
        int start = 1e5;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            start = min(start, a[i]);
            S.insert(a[i]);
        }
        S.erase(S.find(start));
        int num = 1;
        long long ans = start;
        while (!S.empty()) {
            int res = 1e5, tmp = -1;
            for (auto e : S) {
                if (__gcd(start, e) < res) {
                    res = __gcd(start, e);
                    tmp = e;
                }
            }
            if (res == start) break;
            ans += res;
            ++num;
            S.erase(S.find(tmp));
            start = res;
        }
        while (num < n) {
            ans += start;
            ++num;
        }
        cout << ans << endl;
    }
    return 0;
}

