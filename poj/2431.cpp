#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    int l, p;
    cin >> l >> p;
    a.push_back(make_pair(0, 0));
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int ans = 0;
    bool flag = true;
    priority_queue<int> pq;
    for (int i = 0; i <= n; ++i) {
        while (p < l - a[i].first) {
            if (pq.empty()) {
                flag = false;
                break;
            }
            int e = pq.top();
            pq.pop();
            p += e;
            ++ans;
        }
        if (flag == false) break;
        p -= l - a[i].first;
        l = a[i].first;
        pq.push(a[i].second);
    }
    if (!flag) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}

