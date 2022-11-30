#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(m), p(m), q(m);
    vector<vector<int>> G(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i] >> p[i] >> q[i];
        if (q[i] != 0) G[q[i] - 1].push_back(i);
    }
    vector<int> f(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        if (q[i] != 0) continue;
        if (G[i].size() == 0) {
            for (int j = n; j >= v[i]; --j) {
                f[j] = max(f[j], f[j - v[i]] + v[i] * p[i]);
            }
        } else if (G[i].size() == 1) {
            for (int j = n; j >= v[i]; --j) {
                f[j] = max(f[j], f[j - v[i]] + v[i] * p[i]);
                if (j - v[i] - v[G[i][0]] >= 0) {
                    f[j] = max(f[j], f[j - v[i] - v[G[i][0]]] + v[i] * p[i] + v[G[i][0]] * p[G[i][0]]);
                }
            }
        } else {
            for (int j = n; j >= v[i]; --j) {
                f[j] = max(f[j], f[j - v[i]] + v[i] * p[i]);
                if (j - v[i] - v[G[i][0]] >= 0) {
                    f[j] = max(f[j], f[j - v[i] - v[G[i][0]]] + v[i] * p[i] + v[G[i][0]] * p[G[i][0]]);
                }
                if (j - v[i] - v[G[i][1]] >= 0) {
                    f[j] = max(f[j], f[j - v[i] - v[G[i][1]]] + v[i] * p[i] + v[G[i][1]] * p[G[i][1]]);
                }
                if (j - v[i] - v[G[i][0]] - v[G[i][1]] >= 0) {
                    f[j] = max(f[j], f[j - v[i] - v[G[i][0]] - v[G[i][1]]] + v[i] * p[i] + v[G[i][0]] * p[G[i][0]] + v[G[i][1]] * p[G[i][1]]);
                }
            }
        }
    }
    cout << f[n] << endl;
    return 0;
}

