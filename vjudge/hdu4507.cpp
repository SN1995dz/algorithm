#include <bits/stdc++.h>

using namespace std;

struct node {
    long long cnt, sum, sqsum;
    node() : cnt(-1), sum(-1), sqsum(-1){}
    node(long long cnt, long long sum, long long sqsum) : cnt(cnt), sum(sum), sqsum(sqsum){}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<int> a;
    const int MOD = 1e9 + 7;
    vector<long long> p10(19);
    p10[0] = 1;
    for (int i = 1; i < 19; ++i) {
        p10[i] = p10[i - 1] * 10 % MOD;
    }
    vector<vector<vector<node>>> f(19, vector<vector<node>>(7, vector<node>(7)));
    function<node(int, int, int, bool, bool)> dfs = [&](int pos, int sum, int mod, bool smaller, bool positive) {
        if (pos < 0) {
            if (sum != 0 && mod != 0) return node(1, 0, 0);
            return node(0, 0, 0);
        }
        if (smaller && positive && f[pos][sum][mod].cnt != -1) return f[pos][sum][mod];
        int up = smaller ? 9 : a[pos];
        node res(0, 0, 0);
        for (int i = 0; i <= up; ++i) {
            if (i == 7) continue;
            node tmp = dfs(pos - 1, (sum + i) % 7, (mod * 10 + i) % 7, smaller || i < up, positive || i > 0);
            res.cnt += tmp.cnt;
            res.sum = (res.sum + tmp.sum + tmp.cnt * i % MOD * p10[pos] % MOD) % MOD;
            res.sqsum = (res.sqsum + tmp.cnt * i % MOD * p10[pos] % MOD * i % MOD * p10[pos] % MOD + 2LL * i * p10[pos] % MOD * tmp.sum % MOD + tmp.sqsum) % MOD;
        }
        if (smaller && positive) f[pos][sum][mod] = res;
        return res;
    };
    auto solve = [&](long long x) {
        a.clear();
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        return dfs(a.size() - 1, 0, 0, false, false).sqsum;
    };
    int T;
    cin >> T;
    while (T--) {
        long long l, r;
        cin >> l >> r;
        cout << (solve(r) - solve(l - 1) + MOD) % MOD << endl;
    }
    return 0;
}

