#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int m, p;
    cin >> m >> p;
    auto update = [&](vector<vector<long long>> &f, vector<pair<int, int>> &a) {
        int i = a.size() - 1;
        fill(f[i + 1].begin(), f[i + 1].end(), -1);
        pair<int, int> e = a.back();
        for (int j = 0; j < p; ++j) {
            if (f[i][j] == -1) continue;
            f[i + 1][j] = max(f[i + 1][j], f[i][j]);
            f[i + 1][(j + e.first) % p] = max(f[i + 1][(j + e.first) % p], f[i][j] + e.second);
        }
    };
    vector<pair<int, int>> a, b;
    vector<vector<long long>> f(m + 1, vector<long long>(p, -1)), g(m + 1, vector<long long>(p, -1));
    f[0][0] = 0;
    g[0][0] = 0;
    while (m--) {
        string op;
        cin >> op;
        if (op[0] == 'I') {
            int w, v;
            cin >> w >> v;
            if (op[1] == 'F') {
                a.push_back(make_pair(w, v));
                update(f, a);
            } else {
                b.push_back(make_pair(w, v));
                update(g, b);
            }
        } else if (op[0] == 'D') {
            if (op[1] == 'F') {
                if (a.empty()) {
                    int num = (b.size() + 1) / 2;
                    for (int i = num - 1; i >= 0; --i) {
                        a.push_back(b[i]);
                        update(f, a);
                    }
                    vector<pair<int, int>> tmp = b;
                    b.clear();
                    for (int i = num; i < (int)tmp.size(); ++i) {
                        b.push_back(tmp[i]);
                        update(g, b);
                    }
                }
                a.pop_back();
            } else {
                if (b.empty()) {
                    int num = (a.size() + 1) / 2;
                    for (int i = num - 1; i >= 0; --i) {
                        b.push_back(a[i]);
                        update(g, b);
                    }
                    vector<pair<int, int>> tmp = a;
                    a.clear();
                    for (int i = num; i < (int)tmp.size(); ++i) {
                        a.push_back(tmp[i]);
                        update(f, a);
                    }
                }
                b.pop_back();
            }
        } else {
            int l, r;
            cin >> l >> r;
            auto checkIn = [&](int x, int l, int r) {
                if (x < l) return false;
                if (x > r) return false;
                return true;
            };
            long long ans = -1;
            int fi = a.size(), gi = b.size();
            deque<pair<long long, int>> D;
            for (int i = r; i >= l; --i) {
                if (g[gi][i] != -1) {
                    while (!D.empty() && D.back().first <= g[gi][i]) D.pop_back();
                    D.push_back(make_pair(g[gi][i], i));
                    if (f[fi][0] != -1) ans = max(ans, f[fi][0] + g[gi][i]);
                }
            }
            int j = l;
            for (int i = 1; i < p; ++i) {
                --j;
                if (j == -1) j = p - 1;
                if (g[gi][j] != -1) {
                    while (!D.empty() && D.back().first <= g[gi][j]) D.pop_back();
                    D.push_back(make_pair(g[gi][j], j));
                }
                if (f[fi][i] == -1) continue;
                while (!D.empty() && checkIn((i + D.front().second) % p, l, r) == false) D.pop_front();
                if (!D.empty()) {
                    ans = max(ans, f[fi][i] + D.front().first);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}

