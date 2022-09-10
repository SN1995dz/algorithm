//#include <iostream>
#include <cstdio>
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

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    int T;
    //cin >> T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        //cin >> n >> m;
        scanf("%d%d", &n, &m);
        dsu d(n * 2);
        while (m--) {
            //string op;
            char op[2];
            int a, b;
            //cin >> op >> a >> b;
            scanf("%s%d%d", op, &a, &b);
            --a, --b;
            if (op[0] == 'A') {
                if (d.same(a, b)) {
                    //cout << "In the same gang." << endl;
                    printf("In the same gang.\n");
                } else if (d.same(a, b + n)) {
                    //cout << "In different gangs." << endl;
                    printf("In different gangs.\n");
                } else {
                    //cout << "Not sure yet." << endl;
                    printf("Not sure yet.\n");
                }
            } else {
                d.merge(a, b + n);
                d.merge(a + n, b);
            }
        }
    }
    return 0;
}

