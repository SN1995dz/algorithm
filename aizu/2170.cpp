#include <bits/stdc++.h>

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
            //if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            //parent_or_size[x] += parent_or_size[y];
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

        //int size(int a) {
        //    assert(0 <= a && a < _n);
        //    return -parent_or_size[leader(a)];
        //}

        vector<vector<int>> groups() {
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; ++i) {
                leader_buf[i] = leader(i);
                ++group_size[leader_buf[i]];
            }
            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; ++i) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; ++i) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
            return result;
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
    int n, q;
    while (true) {
        cin >> n >> q;
        if (n == 0 && q == 0) break;
        vector<int> p(n, -1);
        for (int i = 1; i < n; ++i) {
            cin >> p[i];
            --p[i];
        }
        string op[q];
        int x[q];
        vector<int> flag(n, 0);
        flag[0] = 1;
        for (int i = 0; i < q; ++i) {
            cin >> op[i] >> x[i] ;
            --x[i];
            if (op[i][0] == 'M') {
                ++flag[x[i]];
            }
        }
        dsu d(n);
        for (int i = 1; i < n; ++i) {
            if (flag[i]) continue;
            d.merge(p[i], i);
        }
        long long ans = 0;
        for (int i = q - 1; i >= 0; --i) {
            if (op[i][0] == 'M') {
                --flag[x[i]];
                if (flag[x[i]] == 0) {
                    d.merge(p[x[i]], x[i]);
                }
            } else {
                ans += d.leader(x[i]) + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

