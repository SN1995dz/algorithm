#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 2) {
            cout << 1 << " " << 3 << endl;
            continue;
        }
        if (n == 3) {
            cout << 3 << " " << 6 << " " << 7 << endl;
            continue;
        }
        int mx = 1e9;
        int l = 1, r = mx - (n - 1), res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if ((long long)mx * (n - 1) - (long long)(n - 1) * (n - 2) / 2 + mid >= (long long)(mx - mid) * (mx - mid)) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        l = res, r = mx - (n - 1), res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if ((long long)mid * (n - 1) + (long long)(n - 1) * (n - 2) / 2 + mx <= (long long)(mx - mid) * (mx - mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        assert(res != -1);
        vector<int> ans;
        long long sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            ans.push_back(res + i);
            sum += res + i;
        }
        ans.push_back(mx);
        sum += mx;
        long long diff = (long long)(mx - res) * (mx - res) - sum;
        int cur = n - 2;
        while (diff) {
            long long tmp = min(diff, (long long)mx - (n - cur - 1) - ans[cur]);
            diff -= tmp;
            ans[cur] += tmp;
            --cur;
        }
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

