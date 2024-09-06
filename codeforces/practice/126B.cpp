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
    cin >> s;
    int n = s.length();
    if (n <= 2) {
        cout << "Just a legend" << endl;
        return 0;
    }
    vector<int> z = zFunction(s);
    int mx = z[1], res = -1;
    for (int i = 2; i < n; ++i) {
        if (i + z[i] == n && mx >= z[i]) {
            res = z[i];
            break;
        }
        mx = max(mx, z[i]);
    }
    if (res == -1) cout << "Just a legend" << endl;
    else cout << s.substr(0, res) << endl;
    return 0;
}

