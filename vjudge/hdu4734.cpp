#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int offset = 5000;
    vector<vector<int>> f(10, vector<int>(10001, -1));
    vector<int> a;
    vector<int> b;
    int T;
    cin >> T;
    function<int(int, int, bool, bool)> dfs = [&](int pos, int remain, bool smaller, bool positive) {
        if (pos < 0) {
            if (remain >= 0) return 1;
            return 0;
        }
        if (smaller && positive && f[pos][remain + offset] != -1) return f[pos][remain + offset];
        int res = 0, up = smaller ? 9 : b[pos];
        for (int i = 0; i <= up; ++i) {
            res += dfs(pos - 1, remain - i * (1 << pos), smaller || i < up, positive || i > 0);
        }
        if (smaller && positive) f[pos][remain + offset] = res;
        return res;
    };
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int A, B;
        cin >> A >> B;
        a.clear();
        while (A) {
            a.push_back(A % 10);
            A /= 10;
        }
        int ceiling = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
            ceiling += a[i] * (1 << i);
        }
        b.clear();
        while (B) {
            b.push_back(B % 10);
            B /= 10;
        }
        cout << dfs(b.size() - 1, ceiling, false, false) << endl;
    }
    return 0;
}

