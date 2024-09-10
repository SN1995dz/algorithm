#include <bits/stdc++.h>

using namespace std;

class ACAM {
    public:
        ACAM() : pool(1) {}

        int insert(string s, int index) {
            int u = 0;
            for (const char ch : s) {
                int o = ch - 'a';
                if (!pool[u].next[o]) {
                    pool[u].next[o] = pool.size();
                    pool.push_back({});
                }
                u = pool[u].next[o];
            }
            if (pool[u].flag == -1) pool[u].flag = index;
            return pool[u].flag;
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

        void query(string s) {
            int u = 0;
            for (const char ch : s) {
                int o = ch - 'a';
                u = pool[u].next[o];
                ++pool[u].ans;
            }
        }

        void topU(vector<int> &res) {
            queue<int> Q;
            for (int u = 1; u < (int)pool.size(); ++u) {
                if (!pool[u].inDeg) Q.push(u);
            }
            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                if (pool[u].flag != -1) res[pool[u].flag] = pool[u].ans;
                int v = pool[u].fail;
                pool[v].ans += pool[u].ans;
                --pool[v].inDeg;
                if (!pool[v].inDeg) Q.push(v);
            }
        }

    private:
        static constexpr int CHARSET = 26;
        struct node {
            node() : flag(-1), fail(0), inDeg(0), ans(0) {
                memset(next, 0, sizeof(next));
            }
            int flag, fail, inDeg, ans;
            int next[CHARSET];
        };
        vector<node> pool;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> rev(n);
    ACAM AM;
    for (int i = 0; i < n; ++i) {
        string p;
        cin >> p;
        rev[i] = AM.insert(p, i);
    }
    AM.getFail();
    string s;
    cin >> s;
    AM.query(s);
    vector<int> ans(n, 0);
    AM.topU(ans);
    for (int i = 0; i < n; ++i) cout << ans[rev[i]] << endl;
    return 0;
}

/*
5
a
bb
aa
abaa
abaaa
abaaabaa
*/

/*
6
0
3
2
1
*/

