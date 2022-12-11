#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class key, class cmp = less<key>>
using ordered_set = tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ordered_set<pair<int, int>> MS;
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long res = 0;
    for (int i = 0; i < k; ++i) {
        MS.insert(make_pair(a[i], i));
        res += a[i];
    }
    for (int i = k; i < m; ++i) {
        auto it = MS.find_by_order(k - 1);
        if (a[i] < it->first) {
            res -= it->first;
            res += a[i];
        }
        MS.insert(make_pair(a[i], i));
    }
    cout << res;
    for (int i = m; i < n; ++i) {
        auto it = MS.find_by_order(k - 1);
        if (a[i] < it->first) {
            res -= it->first;
            res += a[i];
        }
        MS.insert(make_pair(a[i], i));
        it = MS.find_by_order(k - 1);
        if (a[i - m] <= it->first) {
            res -= a[i - m];
            ++it;
            res += it->first;
        }
        MS.erase(make_pair(a[i - m], i - m));
        cout << " " << res;
    }
    cout << endl;
    return 0;
}

