#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector<pair<int, int> > b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i].first >> b[i].second;
    }
    sort(b.begin(), b.end());
    int j = 0;
    priority_queue<int, vector<int>, greater<int> > pq;
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        while (j < n && a[j].first <= b[i].first) {
            pq.push(a[j].second);
            ++j;
        }
        while (!pq.empty() && pq.top() < b[i].first) pq.pop();
        while (!pq.empty() && b[i].second > 0) {
            pq.pop();
            ++ans;
            --b[i].second;
        }
    }
    cout << ans << endl;
    return 0;
}

