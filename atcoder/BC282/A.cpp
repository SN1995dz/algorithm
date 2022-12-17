#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        s.push_back('A' + i);
    }
    cout << s << endl;
    return 0;
}

