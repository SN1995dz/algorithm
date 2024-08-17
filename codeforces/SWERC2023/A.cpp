#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    map<char, int> M;
    M['S'] = 0;
    M['W'] = 1;
    M['E'] = 2;
    M['R'] = 3;
    M['C'] = 4;
    vector<pair<int, int>> a[5];
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a[M[s[0]]].push_back(make_pair(stoi(s.substr(1)), i));
    }
    for (int i = 0; i < 5; ++i) sort(a[i].begin(), a[i].end());
    vector<int> b = {0, 1, 2, 3};
    int ans = n;
    do {
        vector<int> c(n);
        int cnt = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (int)a[b[i]].size(); ++j) {
                c[a[b[i]][j].second] = cnt++;
            }
        }
        for (int j = 0; j < (int)a[4].size(); ++j) c[a[4][j].second] = cnt++;
        int res = 0;
        vector<int> f(n + 1, n + 1);
        f[0] = -1;
        for (int i = 0; i < n; ++i) {
            int tmp = upper_bound(f.begin(), f.end(), c[i]) - f.begin();
            res = max(tmp, res);
            f[tmp] = c[i];
        }
        ans = min(ans, n - res);
    } while (next_permutation(b.begin(), b.end()));
    cout << ans << endl;
    return 0;
}

