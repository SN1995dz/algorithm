#include <bits/stdc++.h>

using namespace std;

class DSU {
    public:
        explicit DSU(int n) : _n(n), parent_or_size(n + n, -1), dis(n + n, 0) {
            for (int i = 0; i < n; ++i) {
                parent_or_size[i] = n + i;
                dis[i] = 1;
            }
        }

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            // if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            dis[y] += -parent_or_size[x];
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
            int par = leader(parent_or_size[a]);
            dis[a] += dis[parent_or_size[a]];
            parent_or_size[a] = par;
            return parent_or_size[a];
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

        int getD(int a) {
            assert(0 <= a && a < _n);
            leader(a);
            return dis[a];
        }
    private:
        int _n;
        // root node: -1 * component size; 0 is abandoned
        // otherwise: parent
        vector<int> parent_or_size;
        vector<int> dis;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int n = 30000;
    DSU d(n);
    while (T--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        --x, --y;
        if (op[0] == 'M') {
            d.merge(y, x);
        } else {
            if (x == y) {
                cout << 0 << endl;
                continue;
            }
            if (d.same(x, y)) {
                int u = d.getD(x), v = d.getD(y);
                if (u > v) swap(u, v);
                cout << v - u - 1 << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}

