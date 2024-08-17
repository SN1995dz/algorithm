#include <bits/stdc++.h>

using namespace std;

// pair<int, int>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> h(n);
    stack<pair<int, int>> S;
    pair<long long, long long> ans = make_pair(0, 1);
    auto F = [&](long long a, long long b) {
        long long tmp = __gcd(a, b);
        a /= tmp;
        b /= tmp;
        return make_pair(a, b);
    };
    auto f_max = [&](pair<long long, long long> a, pair<long long, long long> b) {
        if (a.first * b.second > b.first * a.second) return a;
        return b;
    };
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        pair<int, int> last = make_pair(-1, -1);
        while (!S.empty()) {
            if (S.top().first > h[i]) break;
            last = S.top();
            S.pop();
        }
        if (i > 1 && h[i] > h[i - 1]) {
            if (!S.empty()) {
                int d = S.top().second;
                pair<long long, long long> res = F((h[i] - h[d + 1]) + (long long)(i - (d + 1)) * (h[d] - h[d + 1]), h[d] - h[d + 1]);
                ans = f_max(ans, res);
            } else {
                if (last != make_pair(-1, -1)) {
                    pair<long long, long long> res = F((last.first - h[i - 1]) + (long long)(i - 1 - last.second) * (h[i] - h[i - 1]), h[i] - h[i - 1]);
                    ans = f_max(ans, res);
                }
            }
        }
        S.push(make_pair(h[i], i));
    }
    auto print = [&](pair<long long, long long> &x) {
        if (x.second == 1) cout << x.first << endl;
        else cout << x.first << "/" << x.second << endl;
    };
    print(ans);
    return 0;
}

