#include <bits/stdc++.h>

using namespace std;

struct Trie {
    public:
        Trie() : pool(1) {}

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
        }

        int find(string s) {
            int u = 0;
            for (const char ch : s) {
                int o = ch - 'a';
                if (!pool[u].next[o]) return 0;
                u = pool[u].next[o];
            }
            return pool[u].cnt;
        }

    private:
        static constexpr int CHARSET = 26;
        struct node {
            node() : cnt(0), next(CHARSET, 0) {}
            int cnt;
            vector<int> next;
        };
        vector<node> pool;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    Trie T;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        T.insert(s);
    }
    int m;
    cin >> m;
    set<string> S;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        if (T.find(s)) {
            if (S.count(s)) {
                cout << "REPEAT" << endl;
            } else {
                S.insert(s);
                cout << "OK" << endl;
            }
        } else {
            cout << "WRONG" << endl;
        }
    }
    return 0;
}

