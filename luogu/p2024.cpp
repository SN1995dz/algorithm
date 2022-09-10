#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct dsu {
    public:
        dsu() : _n(0) {}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1){}

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

        int leader(int a) {
            assert(0 <= a && a < _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    dsu d(3 * n);
    int ans = 0;
    while (k--) {
        int D, X, Y;
        cin >> D >> X >> Y;
        if (X > n || Y > n) {
            ++ans;
            continue;
        }
        --X, --Y;
        if (D == 1) {
            if (d.same(X, Y + n) || d.same(X, Y + 2 * n)) {
                ++ans;
                continue;
            }
            d.merge(X, Y);
            d.merge(X + n, Y + n);
            d.merge(X + 2 * n, Y + 2 * n);
        } else {
            if (d.same(X, Y) || d.same(X, Y + 2 * n)) {
                ++ans;
                continue;
            }
            d.merge(X, Y + n);
            d.merge(X + n, Y + 2 * n);
            d.merge(X + 2 * n, Y);
        }
    }
    cout << ans << endl;
    return 0;
}

