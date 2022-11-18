#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string Ts, Te;
    int n;
    cin >> Ts >> Te >> n;
    auto calc = [&](string s) {
        int res = 0;
        for (int i = 0; i < (int)s.length(); ++i) {
            if (s[i] == ':') {
                res += (s[i + 1] - '0') * 10 + s[i + 2] - '0';
                int h = 0;
                for (int j = 0; j < i; ++j) {
                    h *= 10;
                    h += s[j] - '0';
                }
                res += h * 60;
                break;
            }
        }
        return res;
    };
    int W = calc(Te) - calc(Ts);
    vector<int> w, v, p;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if (c == 0) {
            w.push_back(a);
            v.push_back(b);
            p.push_back(0);
        } else {
            int k = 1;
            while (c >= k) {
                w.push_back(a * k);
                v.push_back(b * k);
                p.push_back(1);
                c -= k;
                k *= 2;
            }
            if (c) {
                w.push_back(a * c);
                v.push_back(b * c);
                p.push_back(1);
            }
        }
    }
    vector<int> f(W + 1, 0);
    n = w.size();
    for (int i = 0; i < n; ++i) {
        if (p[i] == 0) {
            for (int j = w[i]; j <= W; ++j) {
                f[j] = max(f[j], f[j - w[i]] + v[i]);
            }
        } else {
            for (int j = W; j >= w[i]; --j) {
                f[j] = max(f[j], f[j - w[i]] + v[i]);
            }
        }
    }
    cout << f[W] << endl;
    return 0;
}

