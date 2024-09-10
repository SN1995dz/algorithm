#include <bits/stdc++.h>

using namespace std;

class ACAM {
    public:
        ACAM() : pool(1) {}

        void insert(string s) {
            int u = 0;
            for (const char ch : s) {
                int o = ch - 'a';
                if (!pool[u].next[o]) {
                    pool[u].next[o] = pool.size();
                    pool.push_back({});
                }
                u = pool[u].next[o];
            }
            ++pool[u].cnt;
            pool[u].state = 1 << (s.length() - 1);
        }

        void getFail() {
            queue<int> Q;
            int u = 0;
            for (int o = 0; o < CHARSET; ++o) {
                if (pool[u].next[o]) Q.push(pool[u].next[o]);
            }
            while (!Q.empty()) {
                u = Q.front();
                Q.pop();
                pool[u].state |= pool[pool[u].fail].state;
                for (int o = 0; o < CHARSET; ++o) {
                    if (pool[u].next[o]) {
                        pool[pool[u].next[o]].fail = pool[pool[u].fail].next[o];
                        ++pool[pool[pool[u].fail].next[o]].inDeg;
                        Q.push(pool[u].next[o]);
                    } else {
                        pool[u].next[o] = pool[pool[u].fail].next[o];
                    }
                }
            }
        }

        int query(string s) {
            int n = s.length();
            int u = 0;
            int res = 0, cur = 1;
            for (int i = 0; i < n; ++i) {
                int o = s[i] - 'a';
                u = pool[u].next[o];
                if (cur & pool[u].state) {
                    cur = ((cur << 1) & ((1 << 20) - 1)) | 1;
                    res = i + 1;
                } else {
                    cur = (cur << 1) & ((1 << 20) - 1);
                }
            }
            return res;
        }

    private:
        static constexpr int CHARSET = 26;
        struct node {
            node() : cnt(0), fail(0), inDeg(0), ans(0), state(0) {
                memset(next, 0, sizeof(next));
            }
            int cnt, fail, inDeg, ans, state;
            int next[CHARSET];
        };
        vector<node> pool;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    ACAM AM;
    for (int i = 0; i < n; ++i) {
        string p;
        cin >> p;
        AM.insert(p);
    }
    AM.getFail();
    while (m--) {
        string s;
        cin >> s;
        cout << AM.query(s) << endl;
    }
    return 0;
}

