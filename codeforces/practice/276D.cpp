#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long l, r;
    cin >> l >> r;
    long long ans = 0;
    for (int i = 60; i >= 0; --i) {
        int a = l >> i & 1;
        int b = r >> i & 1;
        if (a != b) {
            for (int j = i; j >= 0; --j) {
                ans |= 1LL << j;
            }
            break;
        }
    }
    cout << ans << endl;
    return 0;
}

