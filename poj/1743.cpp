#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

template <typename T>
vector<int> getSA(int n, const T &s, int char_bound=256) {
    vector<int> a(n);
    if (n == 0) return a;
    assert(char_bound != -1);
    if (char_bound != -1) {
        vector<int> aux(char_bound, 0);
        for (int i = 0; i < n; ++i) ++aux[s[i]];
        int sum = 0;
        for (int i = 0; i < char_bound; ++i) {
            int add = aux[i];
            aux[i] = sum;
            sum += add;
        }
        for (int i = 0; i < n; ++i) a[aux[s[i]]++] = i;
    }
    vector<int> sorted_by_second(n);
    vector<int> ptr_group(n);
    vector<int> new_group(n);
    vector<int> group(n);
    group[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
        group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
    }
    int cnt = group[a[n - 1]] + 1;
    int step = 1;
    while (cnt < n) {
        int at = 0;
        for (int i = n - step; i < n; ++i) sorted_by_second[at++] = i;
        for (int i = 0; i < n; ++i) {
            if (a[i] - step >= 0) {
                sorted_by_second[at++] = a[i] - step;
            }
        }
        for (int i = n - 1; i >= 0; --i) ptr_group[group[a[i]]] = i;
        for (int i = 0; i < n; ++i) {
            int x = sorted_by_second[i];
            a[ptr_group[group[x]]++] = x;
        }
        new_group[a[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (group[a[i]] != group[a[i - 1]]) {
                new_group[a[i]] = new_group[a[i - 1]] + 1;
            } else {
                int pre = (a[i - 1] + step >= n ? -1 : group[a[i - 1] + step]);
                int cur = (a[i] + step >= n ? -1 : group[a[i] + step]);
                new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
            }
        }
        swap(group, new_group);
        cnt = group[a[n - 1]] + 1;
        step <<= 1;
    }
    return a;
}

template <typename T>
vector<int> getHeight(int n, const T &s, const vector<int> &sa) {
    assert((int)sa.size() == n);
    vector<int> rk(n);
    for (int i = 0; i < n; ++i) rk[sa[i]] = i;

    vector<int> Height(n, 0);
    for (int i = 0, k = 0; i < n; ++i) {
        if (k) --k;
        if (rk[i] == n - 1) k = 0;
        else {
            int j = sa[rk[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            Height[rk[i] + 1] = k;
        }
    }
    return Height;
}

template <typename T>
vector<int> getSA(const T &s, int char_bound=256) {
    return getSA((int)s.size(), s, char_bound);
}

template <typename T>
vector<int> getHeight(const T &s, const vector<int> &sa) {
    return getHeight((int)s.size(), s, sa);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n && n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (n < 10) {
            cout << 0 << endl;
            continue;
        }
        vector<int> s(n - 1);
        for (int i = 1; i < n; ++i) s[i - 1] = a[i] - a[i - 1] + 88;
        vector<int> sa = getSA(s, 88 + 87 + 1);
        vector<int> H = getHeight(s, sa);
        int ans = 0, l = 4, r = (n - 1) / 2;
        while (l <= r) {
            int mid = (l + r) / 2;
            int minPos = n - 1, maxPos = -1;
            bool flag = false;
            for (int i = 1; i < n - 1; ++i) {
                if (H[i] < mid) {
                    if (maxPos != -1) {
                        if (maxPos - minPos >= mid + 1) {
                            flag = true;
                            break;
                        }
                    }
                    minPos = n - 1, maxPos = -1;
                } else {
                    minPos = min(minPos, sa[i - 1]);
                    minPos = min(minPos, sa[i]);
                    maxPos = max(maxPos, sa[i - 1]);
                    maxPos = max(maxPos, sa[i]);
                }
            }
            if (maxPos != -1) {
                if (maxPos - minPos >= mid + 1) flag = true;
            }
            if (flag) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (ans) cout << ans + 1 << endl;
        else cout << 0 << endl;
    }
    return 0;
}

