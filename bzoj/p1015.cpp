#include <bits/stdc++.h>

using namespace std;

class DSU {
    public:
        explicit DSU(int n) : _n(n), parent_or_size(n + n, -1) {
            for (int i = 0; i < n; ++i) {
                parent_or_size[i] = n + i;
            }
        }

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

        bool same(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return leader(a) == leader(b);
        }

        void move(int a, int b) {
            // a move to b
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return;
            ++parent_or_size[x];
            --parent_or_size[y];
            parent_or_size[a] = y;
        }

        int leader(int a) {
            assert(0 <= a && a < _n + _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }
    private:
        int _n;
        // root node: -1 * component size; 0 is abandoned
        // otherwise: parent
        vector<int> parent_or_size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> x(m), y(m);
    DSU d(n);
    vector<vector<int>> G(n);
    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i];
        G[x[i]].push_back(y[i]);
        G[y[i]].push_back(x[i]);
    }
    int k;
    cin >> k;
    vector<int> a(k);
    vector<bool> isAttacked(n, false);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
        isAttacked[a[i]] = true;
    }
    vector<int> ans;
    int num = n - k;
    for (int i = 0; i < m; ++i) {
        if (isAttacked[x[i]] || isAttacked[y[i]]) continue;
        if (!d.same(x[i], y[i])) {
            --num;
            d.merge(x[i], y[i]);
        }
    }
    ans.push_back(num);
    for (int i = k - 1; i >= 0; --i) {
        ++num;
        int u = a[i];
        for (int j = 0; j < (int)G[u].size(); ++j) {
            int v = G[u][j];
            if (isAttacked[v]) continue;
            if (!d.same(u, v)) {
                --num;
                d.merge(u, v);
            }
        }
        isAttacked[u] = false;
        ans.push_back(num);
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i <= k; ++i) cout << ans[i] << endl;
    return 0;
}

