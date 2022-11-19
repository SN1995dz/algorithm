#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, W;
    cin >> n >> W;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int v, w, m;
        cin >> v >> w >> m;
        int k = 1;
        while (k <= m) {
            a.push_back(make_pair(w * k, v * k));
            m -= k;
            k += k;
        }
        if (m) {
            a.push_back(make_pair(w * m, v * m));
        }
    }
    n = a.size();
    vector<int> f(W + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = W; j >= a[i].first; --j) {
            f[j] = max(f[j], f[j - a[i].first] + a[i].second);
        }
    }
    cout << f[W] << endl;
    return 0;
}

