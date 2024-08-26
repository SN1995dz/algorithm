#include <bits/stdc++.h>

using namespace std;

struct Trie01 {
    public:
        Trie01() : pool(1) {}

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

        // int/long long
        void insert(int x) {
            int u = 0;
            vector<int> S;
            for (int i = 0; i < MAXBIT; ++i) {
                S.push_back(u);
                int o = x >> i & 1;
                if (!pool[u].next[o]) {
                    pool[u].next[o] = pool.size();
                    pool.push_back({});
                }
                u = pool[u].next[o];
            }
            ++pool[u].cnt;
            for (int i = MAXBIT - 1; i >= 0; --i) maintain(S[i]);
        }
        /* void insert(int u, int x, int depth) {
            if (depth == MAXBIT) {
                ++pool[u].cnt;
                return;
            }
            if (!pool[u].next[x & 1]) {
                pool[u].next[x & 1] = pool.size();
                pool.push_back({});
            }
            insert(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }*/

        void erase(int x) {
            int u = 0;
            vector<int> S;
            for (int i = 0; i < MAXBIT; ++i) {
                S.push_back(u);
                int o = x >> i & 1;
                u = pool[u].next[o];
            }
            --pool[u].cnt;
            for (int i = MAXBIT - 1; i >= 0; --i) maintain(S[i]);
        }
        /* void erase(int u, int x, int depth) {
            if (depth == MAXBIT) {
                --pool[u].cnt;
                return;
            }
            erase(pool[u].next[x & 1], x >> 1, depth + 1);
            maintain(u);
        }*/

        void addall(int u) {
            swap(pool[u].next[0], pool[u].next[1]);
            if (pool[u].next[0]) addall(pool[u].next[0]);
            maintain(u);
        }

        int getxor() {
            return pool[0].xorv;
        }
        
    private:
        const int MAXBIT = 20;
        struct node {
            node() : cnt(0), xorv(0) {
                memset(next, 0, sizeof(next));
            }
            int cnt, xorv;
            int next[2];
        };
        vector<node> pool;
};

/*
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {  // ch 不是数字时
    if (ch == '-') w = -1;        // 判断是否为负
    ch = getchar();               // 继续读入
  }
  while (ch >= '0' && ch <= '9') {  // ch 是数字时
    x = x * 10 + (ch - '0');  // 将新读入的数字「加」在 x 的后面
    // x 是 int 类型，char 类型的 ch 和 '0' 会被自动转为其对应的
    // ASCII 码，相当于将 ch 转化为对应数字
    // 此处也可以使用 (x<<3)+(x<<1) 的写法来代替 x*10
    ch = getchar();  // 继续读入
  }
  return x * w;  // 数字 * 正负号 = 实际数值
}

void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}

struct edges {
  int node;
  int nxt;
} edge[1000000];

int tot = 0;
int head[500000];

void add(int u, int v) {
  edge[++tot].nxt = head[u];
  head[u] = tot;
  edge[tot].node = v;
}

int par[500000];

void dfs(int u, int p) {
    par[u] = p;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].node;
        if (v == p) continue;
        dfs(v, u);
    }
}

int lazy[500000], v[500000];
int get(int x) {
    if (par[x] == -1) return v[x];
    return lazy[par[x]] + v[x];
}

Trie01 rt[500000];
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    // n = read(), m = read();
    vector<vector<int>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        // u = read(), v = read();
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
        // add(u, v);
        // add(v, u);
    }
    vector<int> par(n, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
        par[u] = p;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == p) continue;
            dfs(v, u);
        }
    };
    dfs(0, -1);
    vector<Trie01> rt(n);
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        // v[i] = read();
        if (par[i] != -1) {
            // rt[par[i]].insert(0, v[i], 0);
            rt[par[i]].insert(v[i]);
        }
    }
    vector<int> lazy(n, 0);
    auto get = [&](int x) {
        if (par[x] == -1) return v[x];
        return lazy[par[x]] + v[x];
    };
    while (m--) {
        int op, x;
        cin >> op >> x;
        // op = read(), x = read();
        --x;
        if (op == 1) {
            ++lazy[x];
            if (par[x] != -1) {
                // if (par[par[x]] != -1) rt[par[par[x]]].erase(0, get(par[x]), 0);
                if (par[par[x]] != -1) rt[par[par[x]]].erase(get(par[x]));
                ++v[par[x]];
                // if (par[par[x]] != -1) rt[par[par[x]]].insert(0, get(par[x]), 0);
                if (par[par[x]] != -1) rt[par[par[x]]].insert(get(par[x]));
            }
            rt[x].addall(0);
        } else if (op == 2) {
            int y;
            cin >> y;
            // y = read();
            // if (par[x] != -1) rt[par[x]].erase(0, get(x), 0);
            if (par[x] != -1) rt[par[x]].erase(get(x));
            v[x] -= y;
            // if (par[x] != -1) rt[par[x]].insert(0, get(x), 0);
            if (par[x] != -1) rt[par[x]].insert(get(x));
        } else {
            int ans = rt[x].getxor();
            if (par[x] != -1) ans ^= get(par[x]);
            cout << ans << endl;
            // write(ans);
            // putchar('\n');
        }
    }
    return 0;
}

