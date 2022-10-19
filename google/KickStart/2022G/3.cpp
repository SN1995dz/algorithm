#include <bits/stdc++.h>

using namespace std;

struct flower {
    int x, y, c;
    flower(int _x, int _y, int _c) : x(_x), y(_y), c(_c) {}
};

void solve() {
    const long long INF = 1e18;
    int n, E;
    cin >> n >> E;
    vector<flower> a;
    int L = 0;
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        L = max(L, x);
        a.push_back(flower(x, y, c));
    }
    sort(a.begin(), a.end(), [&](const flower &a, const flower &b) {
        if (a.y == b.y) return a.x < b.x;
        return a.y > b.y;
    });
    vector<vector<pair<int, int>>> b(n);
    b[0].push_back(make_pair(a[0].x, a[0].c));
    int cur = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i].y != a[i - 1].y) ++cur;
        b[cur].push_back(make_pair(a[i].x, a[i].c));
    }
    int m = cur + 1;
    set<pair<int, long long>> SL, SR;
    SL.insert(make_pair(0, 0));
    SR.insert(make_pair(-L, -E));
    auto ins = [&](set<pair<int, long long>> &S, pair<int, long long> &st) {
        auto it = S.insert(st).first;
        ++it;
        while (it != S.end() && it->second <= st.second) {
            auto tmp = it;
            ++it;
            S.erase(tmp);
        }
    };
    for (int i = 0; i < m; ++i) {
        n = b[i].size();
        auto x = SL.end(), y = SR.end();
        --x, --y;
        {
            auto it = SL.begin();
            pair<int, long long> st = make_pair(it->first, max(it->second, y->second - E));
            SL.erase(it);
            ins(SL, st);
        }
        {
            auto it = SR.begin();
            pair<int, long long> st = make_pair(it->first, max(it->second, x->second - E));
            SR.erase(it);
            ins(SR, st);
        }
        for (int j = 0; j < n; ++j) {
            auto it = SL.upper_bound(make_pair(b[i][j].first, INF));
            --it;
            pair<int, long long> st = make_pair(b[i][j].first, it->second + b[i][j].second);
            if (it->first == b[i][j].first) SL.erase(it);
            ins(SL, st);
        }
        for (int j = n - 1; j >= 0; --j) {
            auto it = SR.upper_bound(make_pair(-b[i][j].first, INF));
            --it;
            pair<int, long long> st = make_pair(-b[i][j].first, it->second + b[i][j].second);
            if (it->first == -b[i][j].first) SR.erase(it);
            ins(SR, st);
        }
    }
    long long ans = 0;
    for (auto e : SL) {
        ans = max(ans, e.second);
    }
    for (auto e : SR) {
        ans = max(ans, e.second);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

