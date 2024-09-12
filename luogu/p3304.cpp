#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, cost;
    edge(int _to, int _cost) : to(_to), cost(_cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<edge>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        G[u].push_back(edge(v, w));
        G[v].push_back(edge(u, w));
    }
    vector<long long> d(n, 0);
    vector<bool> onPath(n, false);
    function<void(int, int, long long, int&)> dfs = [&](int u, int p, long long D, int &longest) {
        d[u] = D;
        if (D > d[longest]) longest = u;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i].to, w = G[u][i].cost;
            if (v == p) continue;
            if (onPath[v]) continue;
            dfs(v, u, D + w, longest);
        }
    };
    int l = 0;
    dfs(0, -1, 0, l);
    fill(d.begin(), d.end(), 0);
    int r = 0;
    dfs(l, -1, 0, r);
    cout << d[r] << endl;
    onPath[r] = true;
    vector<pair<int, int>> s;
    function<bool(int, int, int)> dfs2 = [&](int u, int p, int target) {
        if (u == target) {
            s.push_back(make_pair(target, 0));
            return true;
        }
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i].to, w = G[u][i].cost;
            if (v == p) continue;
            if (dfs2(v, u, target)) {
                onPath[u] = true;
                s.push_back(make_pair(u, w));
                return true;
            }
        }
        return false;
    };
    dfs2(l, -1, r);
    reverse(s.begin(), s.end());
    fill(d.begin(), d.end(), 0);
    vector<int> Longest(n);
    for (int i = 0; i < n; ++i) Longest[i] = i;
    for (int i = 0; i < n; ++i) {
        if (onPath[i]) dfs(i, -1, 0, Longest[i]);
    }
    int ansl = 0, ansr = s.size();
    long long L = 0, R = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (L == d[Longest[s[i].first]]) ansl = i;
        L += s[i].second;
    }
    for (int i = s.size() - 1; i >= 0; --i) {
        R += s[i].second;
        if (R == d[Longest[s[i].first]]) ansr = i;
    }
    cout << ansr - ansl << endl;
    return 0;
}

