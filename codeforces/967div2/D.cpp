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
        vector<int> a(n);
        map<int, int> left, right;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            ++right[a[i]];
        }
        int uni = right.size();
        int point = -1;
        for (int i = 0; i < n; ++i) {
            ++left[a[i]];
            if (right[a[i]] == 1) {
                point = i;
                break;
            }
            --right[a[i]];
        }
        int lpointer = 0;
        vector<int> ans;
        for (int i = 0; i < uni; ++i) {
            auto it = left.begin();
            if (i % 2 == 0) {
                it = left.end();
                --it;
            }
            ans.push_back(it->first);
            while (a[lpointer] != it->first) {
                if (right.count(a[lpointer])) --left[a[lpointer]];
                if (left[a[lpointer]] == 0) {
                    left.erase(left.find(a[lpointer]));
                }
                ++lpointer;
            }
            right.erase(right.find(it->first));
            if (a[point] == it->first) {
                for (int j = point + 1; j < n; ++j) {
                    if (right.count(a[j])) {
                        ++left[a[j]];
                        if (right[a[j]] == 1) {
                            point = j;
                            break;
                        }
                        --right[a[j]];
                    }
                }
            }
            left.erase(it);
            ++lpointer;
        }
        cout << ans.size() << endl;
        for (auto x : ans) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}

