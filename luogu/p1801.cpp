#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> c(m);
    for (int i = 0; i < m; ++i) cin >> c[i];
    int cur = 0, getNum = 0;
    priority_queue<int> a;
    priority_queue<int, vector<int>, greater<int>> b;
    for (int i = 0; i < n; ++i) {
        ++getNum;
        int u;
        cin >> u;
        assert(u <= m);
        assert(getNum <= u);
        while (cur < u) {
            if (a.empty() || c[cur] <= a.top()) {
                a.push(c[cur]);
            } else {
                b.push(c[cur]);
            }
            ++cur;
        }
        while ((int)a.size() > getNum) {
            b.push(a.top());
            a.pop();
        }
        while ((int)a.size() < getNum) {
            a.push(b.top());
            b.pop();
        }
        cout << a.top() << endl;
    }
    return 0;
}

