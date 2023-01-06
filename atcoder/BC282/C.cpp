#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '\"') {
            ++cnt;
        }
        if (s[i] == ',' && cnt % 2 == 0) {
            s[i] = '.';
        }
    }
    cout << s << endl;
    return 0;
}

