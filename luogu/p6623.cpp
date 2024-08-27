#include <bits/stdc++.h>

using namespace std;

class Trie01 {
    public:
        vector<int> rt;

        Trie01() = delete;

        Trie01(int sz) : pool(1) {
            for (int i = 0; i < sz; ++i) rt.push_back(newNode());
        }

        void maintain(int u) {
            pool[u].cnt = 0;
            pool[u].xorv = 0;
            if (pool[u].next[0]) {
                pool[u].cnt += pool[pool[u].next[0]].cnt;
                pool[u].xorv ^= pool[pool[u].next[0]].xorv << 1;
            }
            if (pool[u].next[1]) {
                pool[u].cnt += pool[pool[u].next[1]].cnt;
                pool[u].xorv ^= pool[pool[u].next[1]].xorv << 1 | (pool[pool[u].next[1]].cnt & 1);
            }
        }

        // x: int/long long
        void insert(int u, int x, int depth=0) {
            if (depth == MAXBIT) {
                ++pool[u].cnt;
                return;
            }
            if (!pool[u].next[x & 1]) pool[u].next[x & 1] = newNode();
            insert(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }
        
        // x: int/long long
        void erase(int u, int x, int depth=0) {
            if (depth == MAXBIT) {
                --pool[u].cnt;
                return;
            }
            erase(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }

        void addAll(int u) {
            swap(pool[u].next[0], pool[u].next[1]);
            if (pool[u].next[0]) addAll(pool[u].next[0]);
            maintain(u);
        }

        int getXor(int u) {
            return pool[u].xorv;
        }

        int merge(int a, int b) {
            if (!a) return b;
            if (!b) return a;
            pool[a].cnt += pool[b].cnt;
            pool[a].xorv ^= pool[b].xorv;
            pool[a].next[0] = merge(pool[a].next[0], pool[b].next[0]);
            pool[a].next[1] = merge(pool[a].next[1], pool[b].next[1]);
            return a;
        }
        
    private:
        // MAXBIT: int/long long
        const int MAXBIT = 21;
        struct node {
            node() : cnt(0), xorv(0) {
                next[0] = next[1] = 0;
            }
            int cnt, xorv;
            int next[2];
        };
        vector<node> pool;

        int newNode() {
           pool.push_back({});
           return pool.size() - 1;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> val(n);
    for (int i = 0; i < n; ++i) cin >> val[i];
    vector<vector<int>> G(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        G[p].push_back(i);
    }
    long long ans = 0;
    Trie01 T(n);
    function<void(int)> dfs = [&](int u) {
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            dfs(v);
            T.addAll(T.rt[v]);
            T.rt[u] = T.merge(T.rt[u], T.rt[v]);
        }
        T.insert(T.rt[u], val[u]);
        ans += T.getXor(T.rt[u]);
    };
    dfs(0);
    cout << ans << endl;
    return 0;
}

