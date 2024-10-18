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
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> f(n, vector<long long>(m, 0)), fi(n, vector<long long>(m, 0)), fj(n, vector<long long>(m, 0)), fij(n, vector<long long>(m, 0));
    auto query = [&](int a, int b, int c, int d) {
        long long res = get(f, c, d) * (c + 1) * (d + 1) - get(fi, c, d) * (d + 1) - get(fj, c, d) * (c + 1) + get(fij, c, d);
        if (a > 0) res -= get(f, a - 1, d) * a * (d + 1) - get(fi, a - 1, d) * (d + 1) - get(fj, a - 1, d) * a + get(fij, a - 1, d);
        if (b > 0) res -= get(f, c, b - 1) * (c + 1) * b - get(fi, c, b - 1) * b - get(fj, c, b - 1) * (c + 1) + get(fij, c, b - 1);
        if (a > 0 && b > 0) res += get(f, a - 1, b - 1) * a * b - get(fi, a - 1, b - 1) * b - get(fj, a - 1, b - 1) * a + get(fij, a - 1, b - 1);
        return res;
    };
    int op;
    while (cin >> op) {
        if (op == 1) {
            int a, b, c, d, k;
            cin >> a >> b >> c >> d >> k;
            --a, --b, --c, --d;

            modify(f, a, b, k);
            if (c + 1 < n) modify(f, c + 1, b, -k);
            if (d + 1 < m) modify(f, a, d + 1, -k);
            if (c + 1 < n && d + 1 < m) modify(f, c + 1, d + 1, k);
            
            modify(fi, a, b, k * a);
            if (c + 1 < n) modify(fi, c + 1, b, -k * (c + 1));
            if (d + 1 < m) modify(fi, a, d + 1, -k * a);
            if (c + 1 < n && d + 1 < m) modify(fi, c + 1, d + 1, k * (c + 1));
     
            modify(fj, a, b, k * b);
            if (c + 1 < n) modify(fj, c + 1, b, -k * b);
            if (d + 1 < m) modify(fj, a, d + 1, -k * (d + 1));
            if (c + 1 < n && d + 1 < m) modify(fj, c + 1, d + 1, k * (d + 1));

            modify(fij, a, b, k * a * b);
            if (c + 1 < n) modify(fij, c + 1, b, -k * (c + 1) * b);
            if (d + 1 < m) modify(fij, a, d + 1, -k * a * (d + 1));
            if (c + 1 < n && d + 1 < m) modify(fij, c + 1, d + 1, k * (c + 1) * (d + 1));
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            --a, --b, --c, --d;
            cout << query(a, b, c, d) << endl;
        }
    }
    return 0;
}

