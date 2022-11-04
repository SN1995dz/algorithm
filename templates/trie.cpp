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
    cout.tie(0);
    Trie T;
    T.insert("abc");
    cout << T.find("abc") << endl;
    return 0;
}

