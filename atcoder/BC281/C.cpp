#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long T;
    cin >> n >> T;
    long long sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    T %= sum;
    for (int i = 0; i < n; ++i) {
        if (T > a[i]) {
            T -= a[i];
        } else {
            cout << i + 1 << " " << T << endl;
            break;
        }
    }
    return 0;
}

