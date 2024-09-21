#include <bits/stdc++.h>

using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int T;
    // cin >> T;
    scanf("%d", &T);
    while (T--) {
        int n;
        priority_queue<int> a;
        priority_queue<int, vector<int>, greater<int>> b;
        int num = 0;
        // while (cin >> n && n) {
        while (scanf("%d", &n) && n) {
            if (n == -1) {
                assert(!a.empty());
                // cout << a.top() << endl;
                printf("%d\n", a.top());
                a.pop();
                --num;
            } else {
                ++num;
                if (a.empty() || n <= a.top()) {
                    a.push(n);
                } else {
                    b.push(n);
                }
            }
            while ((int)a.size() < (num + 1) / 2) {
                a.push(b.top());
                b.pop();
            }
            while ((int)a.size() > (num + 1) / 2) {
                b.push(a.top());
                a.pop();
            }
        }
    }
    return 0;
}

