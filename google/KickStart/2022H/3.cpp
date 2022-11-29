#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];
    vector<bool> visited(n + 1, false);
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (visited[i] == false) {
            int l = 0, tmp = i;
            do {
                tmp = p[tmp];
                visited[tmp] = true;
                ++l;
            } while (tmp != i);
            ++cnt[l];
        }
    }
    vector<int> f(n + 1, n);
    f[0] = -1;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] == 0) continue;
        int k = 1;
        while (k <= cnt[i]) {
            for (int j = n - i * k; j >= 0; --j) {
                f[j + i * k] = min(f[j + i * k], f[j] + k);
            }
            cnt[i] -= k;
            k *= 2;
        }
        if (cnt[i]) {
            for (int j = n - i * cnt[i]; j >= 0; --j) {
                f[j + i * cnt[i]] = min(f[j + i * cnt[i]], f[j] + cnt[i]);
            }
        }
    }
    int mn = f[n];
    for (int i = n - 1; i >= 1; --i) {
        f[i] = min(f[i], mn + 1);
        mn = min(mn, f[i]);
    }
    for (int i = 1; i <= n; ++i) {
        cout << f[i] << (i == n ? '\n' : ' ');
    }
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

