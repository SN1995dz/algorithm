#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto modify = [&](vector<vector<long long>> &f, int x, int y, int k) {
        int n = f.size();
        if (n == 0) return;
        int m = f[0].size();
        for (int i = x; i < n; i |= i + 1) {
            for (int j = y; j < m; j |= j + 1) {
                f[i][j] += k;
            }
        }
    };
    auto get = [&](vector<vector<long long>> &f, int x, int y) {
        long long res = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                res += f[i][j];
            }
        }
        return res;
    };
    auto query = [&](vector<vector<long long>> &f, int a, int b, int c, int d) {
        long long res = get(f, c, d);
        if (a > 0) res -= get(f, a - 1, d);
        if (b > 0) res -= get(f, c, b - 1);
        if (a > 0 && b > 0) res += get(f, a - 1, b - 1);
        return res;
    };
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> fenw(n, vector<long long>(m, 0));
    int op;
    while (cin >> op) {
        if (op == 1) {
            int a, b, c, d, k;
            cin >> a >> b >> c >> d >> k;
            --a, --b, --c, --d;
            modify(fenw, a, b, k);
            if (c + 1 < n) modify(fenw, c + 1, b, -k);
            if (d + 1 < m) modify(fenw, a, d + 1, -k);
            if (c + 1 < n && d + 1 < m) modify(fenw, c + 1, d + 1, k);
        } else {
            int x, y;
            cin >> x >> y;
            --x, --y;
            cout << query(fenw, 0, 0, x, y) << endl;
        }
    }
    return 0;
}
