#include <bits/stdc++.h>

using namespace std;

template <typename T>
vector<int> getSA(int n, const T &s, int char_bound=256) {
    vector<int> a(n);
    if (n == 0) return a;
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
    } else {
        iota(a.begin(), a.end(), 0);
        sort(a.begin(), a.end(), [&s](int i, int j) { return s[i] < s[j]; });
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

template<typename T> class sparse_table {
    public:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        sparse_table(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) f[i][0] = v[i];
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    //min or max
                    f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            //min or max
            return min(f[l][k], f[r - (1 << k) + 1][k]);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int caseNum = 0;
    while (cin >> s && s[0] != '#') {
        int n = s.length();
        ++caseNum;
        string rs = s;
        reverse(rs.begin(), rs.end());
        vector<int> sa = getSA(s);
        vector<int> rsa = getSA(rs);
        vector<int> rk(n);
        vector<int> rrk(n);
        for (int i = 0; i < n; ++i) {
            rk[sa[i]] = i;
            rrk[rsa[i]] = i;
        }
        vector<int> H = getHeight(s, sa);
        vector<int> rH = getHeight(rs, rsa);
        sparse_table<int> st(H);
        sparse_table<int> rst(rH);
        sparse_table<int> strk(rk);
        int ans = 1, start = sa[0], len = 1;
        for (int l = 1; l <= n / 2; ++l) {
            for (int i = l; i < n; i += l) {
                int L = min(rk[i], rk[i - l]) + 1, R = max(rk[i], rk[i - l]);
                int right = st.get(L, R);
                L = min(rrk[n - 1 - i], rrk[n - 1 - (i - l)]) + 1, R = max(rrk[n - 1 - i], rrk[n - 1 - (i - l)]);
                int left = rst.get(L, R);
                if ((left + right - 1) / l + 1 > ans) {
                    ans = (left + right - 1) / l + 1;
                    start = i - l - left + 1;
                    start = sa[strk.get(start, start + (left + right - 1) % l)];
                    len = l * ans;
                } else if ((left + right - 1) / l + 1 == ans) {
                    int tmp = i - l - left + 1;
                    tmp = sa[strk.get(tmp, tmp + (left + right - 1) % l)];
                    if (rk[start] > rk[tmp]) {
                        start = tmp;
                        len = l * ans;
                    }
                }
            }
        }
        cout << "Case " << caseNum << ": " << s.substr(start, len) << endl;
    }
    return 0;
}

