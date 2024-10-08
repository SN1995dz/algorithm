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

class DSU {
    public:
        explicit DSU(int n, vector<int> &t) : _n(n), parent_or_size(n + n, -1) {
            for (int i = 0; i < n; ++i) {
                parent_or_size[i] = n + i;
            }
            firstMax.resize(n + n, -1e9);
            secondMax.resize(n + n, -1e9);
            firstMin.resize(n + n, 1e9);
            secondMin.resize(n + n, 1e9);
            for (int i = 0; i < n; ++i) {
                firstMax[n + i] = t[i];
                firstMin[n + i] = t[i];
            }
        }

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            vector<int> tmp;
            tmp.push_back(firstMax[x]);
            tmp.push_back(secondMax[x]);
            tmp.push_back(firstMax[y]);
            tmp.push_back(secondMax[y]);
            sort(tmp.begin(), tmp.end());
            firstMax[x] = tmp[3], secondMax[x] = tmp[2];
            tmp.clear();
            tmp.push_back(firstMin[x]);
            tmp.push_back(secondMin[x]);
            tmp.push_back(firstMin[y]);
            tmp.push_back(secondMin[y]);
            sort(tmp.begin(), tmp.end());
            firstMin[x] = tmp[0], secondMin[x] = tmp[1];
            parent_or_size[y] = x;
            return x;
        }

        bool same(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return leader(a) == leader(b);
        }

        void move(int a, int b) {
            // a move to b
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return;
            ++parent_or_size[x];
            --parent_or_size[y];
            parent_or_size[a] = y;
        }

        int leader(int a) {
            assert(0 <= a && a < _n + _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

        long long getYum(int a) {
            a = leader(a);
            return max((long long)firstMax[a] * secondMax[a], (long long)firstMin[a] * secondMin[a]);
        }
    private:
        int _n;
        // root node: -1 * component size; 0 is abandoned
        // otherwise: parent
        vector<int> parent_or_size;
        vector<int> firstMax, secondMax, firstMin,secondMin;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> sa = getSA(s);
    vector<int> H = getHeight(s, sa);
    vector<int> rk(n);
    for (int i = 0; i < n; ++i) {
        rk[sa[i]] = i;
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i) b[rk[i]] = a[i];
    swap(a, b);
    vector<pair<int, int>> e;
    for (int i = 1; i < n; ++i) {
        e.push_back(make_pair(H[i], i));
    }
    sort(e.begin(), e.end());
    reverse(e.begin(), e.end());
    vector<pair<long long, long long>> ans;
    DSU d(n, a);
    int cur = 0;
    long long num = 0, yum = -1e18;
    for (int i = n - 1; i >= 0; --i) {
        while (cur < n - 1 && e[cur].first >= i) {
            int u = e[cur].second - 1, v = e[cur].second;
            if (!d.same(u, v)) {
                int mu = d.size(u), mv = d.size(v);
                num -= (long long)mu * (mu - 1) / 2;
                num -= (long long)mv * (mv - 1) / 2;
                d.merge(u, v);
                mu = d.size(u);
                num += (long long)mu * (mu - 1) / 2;
                yum = max(yum, d.getYum(u));
            }
            ++cur;
        }
        if (num == 0) ans.push_back(make_pair(num, 0));
        else ans.push_back(make_pair(num, yum));
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}

