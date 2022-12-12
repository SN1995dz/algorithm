#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    function<int(int, int, int)> solve = [&](int k, int L, int R) {
        if (k == -1) return 0;
        int l = L, r = R, tmp = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[mid] >> k & 1) {
                tmp = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int res = 0;
        if (tmp == -1 || tmp == L) {
            res = solve(k - 1, L, R);
        } else {
            res = min(solve(k - 1, L, tmp - 1), solve(k - 1, tmp, R)) + (1 << k);
        }
        return res;
    };
    cout << solve(29, 0, n - 1) << endl;
    return 0;
}

