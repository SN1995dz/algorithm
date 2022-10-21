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
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first;
    for (int i = 0; i < n; ++i) cin >> a[i].second;
    sort(a.begin(), a.end());
    ordered_set<pair<int, int>> MS;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = MS.order_of_key(make_pair(a[i].second + 1, -1));
        ans += (long long)cnt * a[i].first;
        MS.insert(make_pair(a[i].second, i));
    }
    MS.clear();
    for (int i = n - 1; i >= 0; --i) {
        int cnt = MS.size() - MS.order_of_key(make_pair(a[i].second, -1));
        ans -= (long long)cnt * a[i].first;
        MS.insert(make_pair(a[i].second, i));
    }
    cout << ans << endl;
    return 0;
}

