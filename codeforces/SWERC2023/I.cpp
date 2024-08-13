#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m, n;
    cin >> m >> n;
    long long suma = m, sumb = n;
    for (int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        suma += a;
    }
    for (int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        sumb += b;
    }
    if (suma > sumb) cout << "ALICE" <<endl;
    else if (suma == sumb) cout << "TIED" << endl;
    else cout << "BOB" << endl;
    return 0;
}

