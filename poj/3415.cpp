#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

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
    int k;
    while (cin >> k && k) {
        string s, t;
        cin >> s >> t;
        int n = s.length(), m = t.length();
        s.push_back('#');
        for (int i = 0; i < m; ++i) s.push_back(t[i]);
        vector<int> sa = getSA(s);
        vector<int> H = getHeight(s, sa);
        long long ans = 0;
        stack<pair<int, int> > SA, SB;
        long long sumA = 0, sumB = 0;
        assert(H[1] == 0);
        for (int i = 1; i < n + m + 1; ++i) {
            assert(sa[i] != n);
            if (H[i] < k) {
                while (!SA.empty()) SA.pop();
                sumA = 0;
                while (!SB.empty()) SB.pop();
                sumB = 0;
                if (sa[i] < n) {
                    SA.push(make_pair(n, 1));
                    sumA += n - k + 1;
                } else {
                    SB.push(make_pair(m, 1));
                    sumB += m - k + 1;
                }
            } else {
                int cntA = 0, cntB = 0;
                while (!SA.empty() && SA.top().first >= H[i]) {
                    sumA -= (long long)(SA.top().first - k + 1) * SA.top().second;
                    sumA += (long long)(H[i] - k + 1) * SA.top().second;
                    cntA += SA.top().second;
                    SA.pop();
                }
                if (cntA) SA.push(make_pair(H[i], cntA));
                while (!SB.empty() && SB.top().first > H[i]) {
                    sumB -= (long long)(SB.top().first - k + 1) * SB.top().second;
                    sumB += (long long)(H[i] - k + 1) * SB.top().second;
                    cntB += SB.top().second;
                    SB.pop();
                }
                if (cntB) SB.push(make_pair(H[i], cntB));
                if (sa[i] < n) {
                    SA.push(make_pair(n, 1));
                    sumA += n - k + 1;
                    ans += sumB;
                } else {
                    SB.push(make_pair(m, 1));
                    sumB += m - k + 1;
                    ans += sumA;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}

