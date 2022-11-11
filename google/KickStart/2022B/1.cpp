#include <bits/stdc++.h>

using namespace std;

void solve() {
    long long a;
    cin >> a;
    int ans = 0;
    auto check = [&](long long x) {
        vector<int> b;
        while (x) {
            b.push_back(x % 10);
            x /= 10;
        }
        for (int i = 0, j = b.size() - 1; i < j; ++i, --j) {
            if (b[i] != b[j]) return false;
        }
        return true;
    };
    for (long long i = 1; i * i <= a; ++i) {
        if (a % i == 0) {
            if (check(i)) ++ans;
            if (a / i != i && check(a / i)) ++ans;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

