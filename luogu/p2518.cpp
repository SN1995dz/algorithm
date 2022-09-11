#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<vector<long long>> C(51, vector<long long>(51, 0));
    C[0][0] = 1;
    for (int i = 1; i <= 50; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    vector<int> a;
    vector<int> cnt(10, 0);
    function<long long(int, bool)> dfs = [&](int pos, bool smaller) {
        if (pos < 0) return (long long)smaller;
        long long res = 0;
        if (smaller) {
            int num = pos + 1;
            res = 1;
            for (int i = 0; i <= 9; ++i) {
                res *= C[num][cnt[i]];
                num -= cnt[i];
            }
            return res;
        }
        int up = smaller ? 9 : a[pos];
        for (int i = 0; i <= up; ++i) {
            if (cnt[i] == 0) continue;
            --cnt[i];
            res += dfs(pos - 1, smaller || i < up);
            ++cnt[i];
        }
        return res;
    };
    auto solve = [&](string s) {
        a.clear();
        for (int i = 0; i < (int)s.length(); ++i) {
            a.push_back(s[i] - '0');
            ++cnt[s[i] - '0'];
        }
        reverse(a.begin(), a.end());
        return dfs(a.size() - 1, false);
    };
    string n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}

