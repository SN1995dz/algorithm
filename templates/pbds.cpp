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
    ordered_set<int> S;
    S.insert(1);
    S.insert(2);
    S.insert(4);
    S.insert(8);
    S.insert(16);

    // 0-based
    cout << *S.find_by_order(1) << endl; // 2
    cout << *S.find_by_order(2) << endl; // 4
    cout << *S.find_by_order(4) << endl; // 16
    cout << (S.end() == S.find_by_order(6)) << endl; // true

    // strictly smaller
    cout << S.order_of_key(-5) << endl; // 0
    cout << S.order_of_key(1) << endl; // 0
    cout << S.order_of_key(3) << endl; // 2
    cout << S.order_of_key(4) << endl; // 2
    cout << S.order_of_key(400) << endl; // 5

    // multiset: pair<int, int>
    ordered_set<pair<int, int>> MS;
    MS.insert(make_pair(1, 0));
    MS.insert(make_pair(1, 1));
    MS.insert(make_pair(1, 2));

    cout << MS.find_by_order(1)->second << endl; // 1
    cout << MS.order_of_key(make_pair(0, 1)) << endl; // 0
    cout << MS.order_of_key(make_pair(1, 0)) << endl; // 0
    cout << MS.order_of_key(make_pair(1, 1)) << endl; // 1
    cout << MS.order_of_key(make_pair(1, 3)) << endl; // 3
    cout << MS.order_of_key(make_pair(3, 0)) << endl; // 3

    ordered_map<int, int> M;
    M[1] = 2;
    M[2] = 4;
    cout << M.find_by_order(1)->first << " " << M.find_by_order(1)->second << endl; // 2 4
    cout << M.order_of_key(1) << endl; // 0
    cout << M.order_of_key(2) << endl; // 1
    cout << M.order_of_key(3) << endl; // 2
    return 0;
}

