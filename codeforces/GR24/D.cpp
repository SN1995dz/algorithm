#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long P;
    cin >> n >> P;
    vector<long long> pow(n + 1);
    pow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pow[i] = pow[i - 1] * i % P;
    }
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1));
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 || j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
            }
        }
    }
    int can = n / 2;
    long long ans = 0;
    for (int i = n / 2; i <= n - 1; ++i) {
        int A = max(0, n - i - 2);
        for (int j = 0; j <= A; ++j) {
            ans = (ans + pow[j + i - 1] * C[A][j] % P * can % P) % P;
        }
        --can;
    }
    ans = ans * n % P;
    cout << ans << endl;
    return 0;
}

