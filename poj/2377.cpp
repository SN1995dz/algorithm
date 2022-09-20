#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

struct dsu {
    public:
        dsu() : _n(0) {}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

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

        //vector<vector<int>> groups() {
        //    vector<int> leader_buf(_n), group_size(_n);
        //    for (int i = 0; i < _n; ++i) {
        //        leader_buf[i] = leader(i);
        //        ++group_size[leader_buf[i]];
        //    }
        //    vector<vector<int>> result(_n);
        //    for (int i = 0; i < _n; ++i) {
        //        result[i].reserve(group_size[i]);
        //    }
        //    for (int i = 0; i < _n; ++i) {
        //        result[leader_buf[i]].push_back(i);
        //    }
        //    result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
        //    return result;
        //}

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
};

struct edge {
    int from, to, cost;
    edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
    friend bool operator < (const edge &a, const edge &b) {
        return a.cost > b.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<edge> a;
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        a.push_back(edge(x, y, z));
    }
    /*sort(a.begin(), a.end(), [&](edge x, edge y) {
        return x.cost > y.cost;
    });*/
    sort(a.begin(), a.end());
    dsu d(n);
    int ans = 0, cnt = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (!d.same(a[i].from, a[i].to)) {
            ++cnt;
            ans += a[i].cost;
            if (cnt == n - 1) break;
            d.merge(a[i].from, a[i].to);
        }
    }
    if (cnt == n - 1) cout << ans << endl;
    else cout << -1 << endl;
    return 0;
}

