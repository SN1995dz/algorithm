#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    map<string, int> M;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        ++M[s];
    }
    string ans = "uh-oh";
    for (auto &kv : M) {
        if (kv.second * 2 > n) {
            ans = kv.first;
        }
    }
    cout << ans << endl;
    return 0;
}

