#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    map<pair<int, int>, int> M;
    int cnt = 0;
    vector<int> a;
    vector<pair<int, int>> b;
    for (int len = 1; len <= n; len = len + len + 1) {
        a.push_back(len);
        for (int i = 1; i + len - 1 <= n; ++i) {
            M[make_pair(i, i + len - 1)] = ++cnt;
            b.push_back(make_pair(i, i + len - 1));
        }
    }
    cout << cnt << endl;
    cout.flush();
    for (int i = 0; i < cnt; ++i) {
        cout << b[i].first << " " << b[i].second << endl;
        cout.flush();
    }
    int q;
    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;
        for (int i = 0; i < (int)a.size(); ++i) {
            if (a[i] * 2 >= R - L + 1) {
                cout << M[make_pair(L, L + a[i] - 1)] << " " << M[make_pair(R - a[i] + 1, R)] << endl;
                cout.flush();
                break;
            }
        }
    }
    return 0;
}

