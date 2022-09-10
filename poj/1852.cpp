#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int L, n;
        cin >> L >> n;
        vector<int> a(n);
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) {
            ans1 = max(ans1, min(a[i], L - a[i]));
            ans2 = max(ans2, max(a[i], L - a[i]));
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}

