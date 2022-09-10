#include <iostream>
#include <vector>

using namespace std;

vector<int> a;
int offset = 50;
vector<vector<int> > f(50, vector<int>(101, -1));

int dfs(int pos, int nz, bool smaller, bool positive) {
    if (pos < 0) {
        if (nz <= 0) return 1;
        return 0;
    }
    if (smaller && positive && f[pos][nz + offset] != -1) return f[pos][nz + offset];
    int res = 0, up = smaller ? 1 : a[pos];
    for (int i = 0; i <= up; ++i) {
        if (i == 0) {
            if (positive) {
                res += dfs(pos - 1, nz - 1, smaller || i < up, positive || i > 0); 
            } else {
                res += dfs(pos - 1, nz, smaller || i < up, positive || i > 0);
            }
        }
        if (i == 1) res += dfs(pos - 1, nz + 1, smaller || i < up, positive || i > 0);
    }
    if (smaller && positive) f[pos][nz + offset] = res;
    return res;
}

int solve(int x) {
    a.clear();
    while (x) {
        a.push_back(x & 1);
        x >>= 1;
    }
    return dfs(a.size() - 1, 0, false, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

