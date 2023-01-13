#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        vector<pair<int, int>> b;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
                if (a[i][j] == 1) ++cnt;
            }
            b.push_back(make_pair(cnt, i));
            sum += cnt;
        }
        if (sum % n != 0) {
            cout << -1 << endl;
            continue;
        }
        int x = sum / n;
        vector<pair<int, int>> c, d;
        for (auto &e : b) {
            if (e.first == x) continue;
            if (e.first > x) {
                c.push_back(e);
            } else {
                d.push_back(e);
            }
        }
        vector<int> ansx, ansy, ansz;
        for (int i = 0, j = 0; i < (int)c.size(); ++i) {
            while (c[i].first > x) {
                int tmp = min(c[i].first - x, x - d[j].first);
                int u = c[i].second, v = d[j].second;
                for (int k = 0; k < m; ++k) {
                    if (a[u][k] == 1 && a[v][k] == 0) {
                        swap(a[u][k], a[v][k]);
                        ansx.push_back(u + 1);
                        ansy.push_back(v + 1);
                        ansz.push_back(k + 1);
                        --c[i].first;
                        ++d[j].first;
                        --tmp;
                        if (tmp == 0) break;
                    }
                }
                if (x - d[j].first == 0) ++j;
            }
        }
        cout << ansx.size() << endl;
        for (int i = 0; i < (int)ansx.size(); ++i) {
            cout << ansx[i] << " " << ansy[i] << " " << ansz[i] << endl;
        }
    }
    return 0;
}

