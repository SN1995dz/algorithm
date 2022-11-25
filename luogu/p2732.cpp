#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> a(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            pair<int, int> x;
            cin >> x.first >> x.second;
            a[i].push_back(x);
        }
        cin >> p[i];
    }
    vector f(6, vector(6, vector(6, vector(6, vector<int>(6, 1e5)))));
    f[0][0][0][0][0] = 0;
    int m;
    cin >> m;
    vector<int> M(1000, -1);
    vector<int> tar(5, 0);
    for (int i = 0; i < m; ++i) {
        int C, K, P;
        cin >> C >> K >> P;
        M[C] = i;
        tar[i] = K;
        vector<pair<int, int>> tmp;
        tmp.push_back(make_pair(C, 1));
        a.push_back(tmp);
        p.push_back(P);
    }
    n = a.size();
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        vector<int> b(5, 0);
        for (int j = 0; j < (int)a[i].size(); ++j) {
            if (M[a[i][j].first] == -1) {
                flag = true;
                break;
            }
            b[M[a[i][j].first]] = a[i][j].second;
        }
        if (flag) continue;
        for (int j1 = b[0]; j1 <= 5; ++j1) {
            for (int j2 = b[1]; j2 <= 5; ++j2) {
                for (int j3 = b[2]; j3 <= 5; ++j3) {
                    for (int j4 = b[3]; j4 <= 5; ++j4) {
                        for (int j5 = b[4]; j5 <= 5; ++j5) {
                            f[j1][j2][j3][j4][j5] = min(f[j1][j2][j3][j4][j5], f[j1 - b[0]][j2 - b[1]][j3 - b[2]][j4 - b[3]][j5 - b[4]] + p[i]);
                        }
                    }
                }
            }
        }
    }
    cout << f[tar[0]][tar[1]][tar[2]][tar[3]][tar[4]] << endl;
    return 0;
}

