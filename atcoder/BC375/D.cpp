#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    cin >> S;
    int n = S.length();
    vector<int> cnt(26, 0);
    vector<long long> sum(26, 0);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int o = S[i] - 'A';
        ans += (long long)cnt[o] * i - sum[o] - cnt[o];
        ++cnt[o];
        sum[o] += i;
    }
    cout << ans << endl;
    return 0;
}

