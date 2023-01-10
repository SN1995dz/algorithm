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
        int x;
        cin >> x;
        vector<int> a;
        for (int i = 1; i < n; ++i) {
            int tmp;
            cin >> tmp;
            if (tmp > x) a.push_back(tmp);
        }
        sort(a.begin(), a.end());
        for (auto &y : a) {
            if (y <= x) continue;
            x = (x + y + 1) / 2;
        }
        cout << x << endl;
    }
    return 0;
}

