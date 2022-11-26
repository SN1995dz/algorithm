#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a;
        if (n % 2 == 0) {
            a.push_back(1);
            a.push_back(3);
            for (int i = 2; i < n; ++i) a.push_back(2);
        } else {
            for (int i = 0; i < n; ++i) a.push_back(2);
        }
        for (int i = 0; i < n; ++i) {
            cout << a[i] << (i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

