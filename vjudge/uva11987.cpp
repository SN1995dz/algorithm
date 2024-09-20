#include <bits/stdc++.h>

using namespace std;

class DSU {
    public:
        explicit DSU(int n) : _n(n), parent_or_size(n + n, -1), sum(n + n, 0){
            for (int i = 0; i < n; ++i) {
                parent_or_size[i] = n + i;
                sum[n + i] = i + 1;
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
            sum[x] += sum[y];
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
            sum[y] += a + 1;
            sum[x] -= a + 1;
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

        long long getSum(int a) {
            assert(0 <= a && a < _n);
            return sum[leader(a)];
        }
    private:
        int _n;
        // root node: -1 * component size; 0 is abandoned
        // otherwise: parent
        vector<int> parent_or_size;
        vector<long long> sum;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        DSU d(n);
        while (m--) {
            int op, p;
            cin >> op >> p;
            if (op == 1) {
                int q;
                cin >> q;
                --p, --q;
                d.merge(p, q);
            } else if (op == 2) {
                int q;
                cin >> q;
                --p, --q;
                d.move(p, q);
            } else {
                --p;
                cout << d.size(p) << " " << d.getSum(p) << endl;
            }
        }
    }
    return 0;
}

