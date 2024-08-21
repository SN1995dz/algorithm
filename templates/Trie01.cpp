#include <bits/stdc++.h>

using namespace std;

struct Trie01 {
    public:
        explicit Trie01() : pool(1) {}

        // int/long long
        void insert(int x) {
            int u = 0;
            for (int i = MAXBIT - 1; i >= 0; --i) {
                int o = ((x >> i) & 1);
                if (!pool[u].next[o]) {
                    pool[u].next[o] = pool.size();
                    pool.push_back({});
                }
                u = pool[u].next[o];
            }
            ++pool[u].cnt;
        }

        // int/long long
        int findMax(int x) {
            int res = 0, u = 0;
            for (int i = MAXBIT - 1; i >= 0; --i) {
                int o = ((x >> i) & 1);
                if (pool[u].next[o ^ 1]) {
                    u = pool[u].next[o ^ 1];
                    res |= 1 << i;
                } else {
                    u = pool[u].next[o];
                }
            }
            return res;
        }

    private:
        // int 31/long long 63
        static constexpr int MAXBIT = 31;
        struct node {
            node() : cnt(0), next(2, 0) {}
            int cnt;
            vector<int> next;
        };
        vector<node> pool;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }
    vector<int> d(n, -1);
    Trie01 T;
    int ans = 0;
    function<void(int, int)> dfs = [&](int u, int fa) {
        ans = max(ans, T.findMax(d[u]));
        T.insert(d[u]);
        for (int i = 0; i < (int)G[u].size(); ++i) {
            auto e = G[u][i];
            if (e.first == fa) continue;
            d[e.first] = d[u] ^ e.second;
            dfs(e.first, u);
        }
    };
    d[0] = 0;
    dfs(0, -1);
    cout << ans << endl;
    return 0;
}

