#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<pair<int, int>, string>> a;
    for (int i = 0; i < n; ++i) {
        string name;
        int p;
        vector<int> e(6);
        cin >> name >> p;
        for (int j = 0; j < 6; ++j) cin >> e[j];
        sort(e.begin(), e.end());
        int s = p * 10;
        for (int i = 1; i < 5; ++i) {
            s += e[i];
        }
        a.push_back(make_pair(make_pair(s, -i), name));
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        if (a[2].first.first > a[i].first.first) break;
        cout << a[i].second << " " << a[i].first.first << endl;
    }
    return 0;
}

