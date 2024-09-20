#include <iostream>
#include <vector>
#include <cassert>
#include <set>

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
        vector<int> s;
        vector<string> t(n);
        vector<int> ind;
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
            for (int j = 0; j < (int)t[i].length(); ++j) {
                s.push_back(t[i][j] - 'a');
                ind.push_back(i);
            }
            if (i != n - 1) {
                s.push_back(-1 - i);
                ind.push_back(-1);
            }
        }
        int m = s.size();
        for (int i = 0; i < m; ++i) s[i] += n;
        vector<int> sa = getSA(s);
        vector<int> H = getHeight(s, sa);
        int l = 1, r = t[0].length(), res = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool check = false;
            set<int> S;
            for (int i = n - 1; i < m; ++i) {
                if (H[i] >= mid) {
                    S.insert(ind[sa[i - 1]]);
                    S.insert(ind[sa[i]]);
                } else {
                    S.clear();
                }
                if ((int)S.size() > n / 2) {
                    check = true;
                    break;
                }
            }
            if (check) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (res == 0) {
            cout << "?" << endl;
            cout << endl;
            continue;
        }
        set<int> S;
        vector<int> ans;
        bool flag = true;
        for (int i = n; i < m; ++i) {
            if (H[i] >= res) {
                S.insert(ind[sa[i - 1]]);
                S.insert(ind[sa[i]]);
            } else {
                S.clear();
                flag = true;
            }
            if ((int)S.size() > n / 2 && flag) {
                ans.push_back(sa[i]);
                flag = false;
            }
        }
        for (int i = 0; i < (int)ans.size(); ++i) {
            for (int j = 0; j < res; ++j) {
                cout << (char)('a' + s[ans[i] + j] - n);
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}

