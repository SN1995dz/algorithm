#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k, n;
    cin >> k >> n;
    vector<vector<int>> ans(3, vector<int>(n, -1));
    vector<int> a(k), b(k);
    for (int p = 0; p < k; ++p) cin >> a[p];
    for (int p = 0; p < k; ++p) cin >> b[p];
    vector<int> c11, c12, c22, c13;
    int left = 0;
    for (int p = 0; p < k; ++p) {
        if (a[p] == 3 && b[p] != 1) {
            for (int i = 0; i < 3; ++i) {
                for (int j = left; j < left + b[p]; ++j) {
                    ans[i][j] = p + 1;
                }
            }
            left += b[p];
            continue;
        }
        if (b[p] == 3 && a[p] != 1) {
            for (int i = 0; i < 3; ++i) {
                for (int j = left; j < left + a[p]; ++j) {
                    ans[i][j] = p + 1;
                }
            }
            left += a[p];
            continue;
        }
        if (a[p] == 1 && b[p] == 1) {
            c11.push_back(p);
            continue;
        }
        if (a[p] == 2 && b[p] == 2) {
            c22.push_back(p);
            continue;
        }
        if (a[p] == 3 || b[p] == 3) {
            c13.push_back(p);
            continue;
        }
        c12.push_back(p);
    }
    int i11 = 0, i12 = 0, i22 = 0, i13 = 0;
    while (i12 < (int)c12.size() && i22 < (int)c22.size()) {
        for (int j = left; j < left + 2; ++j) {
            ans[0][j] = c12[i12] + 1;
        }
        for (int i = 1; i < 3; ++i) {
            for (int j = left; j < left + 2; ++j) {
                ans[i][j] = c22[i22] + 1;
            }
        }
        ++i12, ++i22;
        left += 2;
    }
    while (i12 < (int)c12.size()) {
        for (int tt = i12; tt + 2 < (int)c12.size(); tt += 3, i12 += 3) {
            ans[0][left] = c12[tt] + 1;
            ans[0][left + 1] = c12[tt] + 1;
 
            ans[1][left] = c12[tt + 1] + 1;
            ans[2][left] = c12[tt + 1] + 1;
            
            ans[1][left + 1] = c12[tt + 2] + 1;
            ans[2][left + 1] = c12[tt + 2] + 1;
            left += 2;
        }
        if (i12 >= (int)c12.size()) break;
        ans[0][left] = c11[i11] + 1;
        ans[1][left] = c12[i12] + 1;
        ans[2][left] = c12[i12] + 1;
        ++i12, ++i11;
        left += 1;
    }
    while (i22 < (int)c22.size()) {
        for (int tt = i22, tt13 = i13; tt + 2 < (int)c22.size() && tt13 + 1 < (int)c13.size(); tt += 3, i22 += 3, tt13 += 2, i13 += 2) {
            ans[0][left] = c13[tt13] + 1;
            ans[0][left + 1] = c13[tt13] + 1;
            ans[0][left + 2] = c13[tt13] + 1;
 
            ans[0][left + 3] = c13[tt13 + 1] + 1;
            ans[0][left + 4] = c13[tt13 + 1] + 1;
            ans[0][left + 5] = c13[tt13 + 1] + 1;
 
            ans[1][left] = c22[tt] + 1;
            ans[2][left] = c22[tt] + 1;
            ans[1][left + 1] = c22[tt] + 1;
            ans[2][left + 1] = c22[tt] + 1;
 
            ans[1][left + 2] = c22[tt + 1] + 1;
            ans[2][left + 2] = c22[tt + 1] + 1;
            ans[1][left + 3] = c22[tt + 1] + 1;
            ans[2][left + 3] = c22[tt + 1] + 1;
 
            ans[1][left + 4] = c22[tt + 2] + 1;
            ans[2][left + 4] = c22[tt + 2] + 1;
            ans[1][left + 5] = c22[tt + 2] + 1;
            ans[2][left + 5] = c22[tt + 2] + 1;
            
            left += 6;
        }
        if (i22 >= (int)c22.size()) break; 
        for (int tt = i22, tt13 = i13; tt + 1 < (int)c22.size() && tt13 < (int)c13.size(); tt += 2, i22 += 2, tt13 += 1, i13 += 1) {
            ans[0][left] = c13[tt13] + 1;
            ans[0][left + 1] = c13[tt13] + 1;
            ans[0][left + 2] = c13[tt13] + 1;
            
            ans[0][left + 3] = c11[i11] + 1;
            i11 += 1;
 
            ans[1][left] = c22[tt] + 1;
            ans[2][left] = c22[tt] + 1;
            ans[1][left + 1] = c22[tt] + 1;
            ans[2][left + 1] = c22[tt] + 1;
 
            ans[1][left + 2] = c22[tt + 1] + 1;
            ans[2][left + 2] = c22[tt + 1] + 1;
            ans[1][left + 3] = c22[tt + 1] + 1;
            ans[2][left + 3] = c22[tt + 1] + 1;
 
            left += 4;
        }
        if (i22 >= (int)c22.size()) break; 
        ans[0][left] = c11[i11] + 1;
        ans[0][left + 1] = c11[i11 + 1] + 1;
        ans[1][left] = c22[i22] + 1;
        ans[2][left] = c22[i22] + 1;
        ans[1][left + 1] = c22[i22] + 1;
        ans[2][left + 1] = c22[i22] + 1;
        ++i22;
        i11 += 2;
        left += 2;
    }
    for (int tt13 = i13; tt13 < (int)c13.size(); ++tt13) {
        ans[0][left] = c13[tt13] + 1;
        ans[1][left] = c13[tt13] + 1;
        ans[2][left] = c13[tt13] + 1;
        left += 1;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = left; j < n; ++j) {
            ans[i][j] = c11[i11] + 1;
            ++i11;
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

