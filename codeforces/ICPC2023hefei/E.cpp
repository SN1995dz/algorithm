#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(m));
    vector<int> disc_c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c[i][j];
            disc_c.push_back(c[i][j]);
        }
    }
    sort(disc_c.begin(), disc_c.end());
    disc_c.resize(unique(disc_c.begin(), disc_c.end()) - disc_c.begin());
    int C = disc_c.size();
    vector<vector<int>> row(C), col(C);
    vector<vector<int>> rr(n, vector<int>(m));
    vector<vector<int>> cc(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[i][j] = lower_bound(disc_c.begin(), disc_c.end(), c[i][j]) - disc_c.begin();
            row[c[i][j]].push_back(i);
            rr[i][j] = row[c[i][j]].size() - 1;
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            col[c[i][j]].push_back(j);
            cc[i][j] = col[c[i][j]].size() - 1;
        }
    }
    vector<vector<long long>> l(C), u(C);
    for (int i = 0; i < C; ++i) {
        int rn = row[i].size();
        vector<long long> tmp(rn, 0);
        for (int j = 1; j < rn; ++j) {
            tmp[j] = tmp[j - 1] + (long long)(row[i][j] - row[i][j - 1]) * j;
        }
        l[i] = tmp;
    }
    for (int i = 0; i < C; ++i) {
        int cn = col[i].size();
        vector<long long> tmp(cn, 0);
        for (int j = 1; j < cn; ++j) {
            tmp[j] = tmp[j - 1] + (long long)(col[i][j] - col[i][j - 1]) * j;
        }
        u[i] = tmp;
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int tmp = rr[i][j];
            ans += l[c[i][j]][tmp] * 2;
            tmp = cc[i][j];
            ans += u[c[i][j]][tmp] * 2;
        }
    }
    cout << ans << endl;
    return 0;
}

