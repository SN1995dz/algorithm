#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int hmn = 0, tmn = -1, hmx = 0, tmx = -1;
    vector<pair<int, int>> qmn(n), qmx(n);
    vector<int> ansmn, ansmx;
    for (int i = 0; i < k; ++i) {
        while (tmn >= hmn && qmn[tmn].first >= a[i]) --tmn;
        qmn[++tmn] = make_pair(a[i], i);

        while (tmx >= hmx && qmx[tmx].first <= a[i]) --tmx;
        qmx[++tmx] = make_pair(a[i], i);
    }
    ansmn.push_back(qmn[hmn].first);

    ansmx.push_back(qmx[hmx].first);
    for (int i = k; i < n; ++i) {
        while (tmn >= hmn && qmn[tmn].first >= a[i]) --tmn;
        qmn[++tmn] = make_pair(a[i], i);
        while (tmn >= hmn && qmn[hmn].second <= i - k) ++hmn;
        ansmn.push_back(qmn[hmn].first);

        while (tmx >= hmx && qmx[tmx].first <= a[i]) --tmx;
        qmx[++tmx] = make_pair(a[i], i);
        while (tmx >= hmx && qmx[hmx].second <= i - k) ++hmx;
        ansmx.push_back(qmx[hmx].first);
    }
    for (int i = 0; i <= n - k; ++i) {
        cout << ansmn[i] << (i == n - k ? '\n' : ' ');
    }

    for (int i = 0; i <= n - k; ++i) {
        cout << ansmx[i] << (i == n - k ? '\n' : ' ');
    }
    return 0;
}

