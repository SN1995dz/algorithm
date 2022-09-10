#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, c, f;
    cin >> n >> c >> f;
    n /= 2;
    vector<pair<int, int> > a(c);
    for (int i = 0; i < c; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector<int> l(c, f + 1);
    int sum = 0;
    priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        pq.push(a[i].second);
        sum += a[i].second;
    }
    l[n] = sum;
    for (int i = n + 1; i < c; ++i) {
        pq.push(a[i - 1].second);
        sum += a[i - 1].second;
        sum -= pq.top();
        pq.pop();
        l[i] = sum;
    }
    vector<int> r(c + 2, f + 1);
    sum = 0;
    while (!pq.empty()) pq.pop();
    for (int i = 0; i < n; ++i) {
        pq.push(a[c - i - 1].second);
        sum += a[c - i - 1].second;
    }
    r[c + 1 - n] = sum;
    for (int i = c - n; i >= 2; --i) {
        pq.push(a[i - 1].second);
        sum += a[i - 1].second;
        sum -= pq.top();
        pq.pop();
        r[i] = sum;
    }
    int ans = -1;
    for (int i = 0; i < c; ++i) {
        if ((long long)a[i].second + l[i] + r[i + 2] <= f) {
            ans = max(ans, a[i].first);
        }
    }
    cout << ans << endl;
    return 0;
}

