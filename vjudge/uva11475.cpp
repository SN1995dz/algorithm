#include <bits/stdc++.h>

using namespace std;

// z[i] = max{x}->a[0..x-1]=a[i..i+x-1]
template<typename T>
vector<int> zFunction(const T& a) {
    int n = a.size();
    vector<int> z(n);
    z[0] = n;
    int l = -1, r = -1;
    for (int i = 1; i < n; ++i) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < n && a[i + z[i]] == a[z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        int n = s.length();
        string t = s;
        reverse(t.begin(), t.end());
        t.push_back('#');
        t += s;
        vector<int> z = zFunction(t);
        int res = 0;
        for (int i = n + 1; i <= n + n; ++i) {
            if (i - n - 1 + z[i] == n) {
                res = z[i];
                break;
            }
        }
        string ans;
        for (int i = 0; i < n - res; ++i) ans.push_back(s[i]);
        reverse(ans.begin(), ans.end());
        cout << s;
        cout << ans << endl;
    }
    return 0;
}

