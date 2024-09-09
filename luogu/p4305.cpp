#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        unordered_set<int> S;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (S.count(x)) continue;
            S.insert(x);
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}

