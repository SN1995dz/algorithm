#include <bits/stdc++.h>

using namespace std;

template<typename T> class SegTree {
    public:
        vector<int> rt;

        SegTree() = delete;

        SegTree(int sz, int _n) : pool(1), n(_n) {
            assert(n > 0);
            for (int i = 0; i < sz; ++i) rt.push_back(newNode());
        }

        SegTree(const vector<T> &v) : pool(1) {
            n = v.size();
            assert(n > 0);
            rt.push_back(newNode());
            function<void(int, int, int)> build = [&](int x, int l, int r) {
                if (l == r) {
                    pool[x].val = v[l];
                    return;
                }
                int y = (l + r) >> 1;
                pool[x].next[0] = newNode();
                pool[x].next[1] = newNode();
                build(pool[x].next[0], l, y);
                build(pool[x].next[1], y + 1, r);
            };
            build(rt.back(), 0, n - 1);
        }
        
        int modify(int x, int p, const T &v) {
            assert(0 <= p && p <= n - 1);
            rt.push_back(newNode());
            modify(x, rt.back(), 0, n - 1, p, v);
            return rt.back();
        }

        T get(int x, int p) {
            assert(0 <= p && p <= n - 1);
            return get(x, 0, n - 1, p).val;
        }

    private:
        struct node {
            node() : val() {
                next[0] = next[1] = 0;
            }
            
            T val;
            array<int, 2> next;
        };

        int n;
        vector<node> pool;

        int newNode() {
            pool.push_back({});
            return pool.size() - 1;
        }

        void modify(int x, int q, int l, int r, int p, const T &v) {
            if (l == r) {
                pool[q].val = v;
                return;
            }
            int y = (l + r) >> 1;
            if (p <= y) {
                pool[q].next[1] = pool[x].next[1];
                pool[q].next[0] = newNode();
                modify(pool[x].next[0], pool[q].next[0], l, y, p, v);
            }
            else {
                pool[q].next[0] = pool[x].next[0];
                pool[q].next[1] = newNode();
                modify(pool[x].next[1], pool[q].next[1], y + 1, r, p, v);
            }
        }

        node get(int x, int l, int r, int p) {
            if (l == r) return pool[x];
            int y = (l + r) >> 1;
            node res;
            if (p <= y) {
                res = get(pool[x].next[0], l, y, p);
            } else {
                res = get(pool[x].next[1], y + 1, r, p);
            }
            return res;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegTree<int> st(a);
    vector<int> history(m + 1);
    history[0] = st.rt[0];
    for (int i = 1; i <= m; ++i) {
        int version, op;
        cin >> version >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            --x;
            history[i] = st.modify(history[version], x, y);
        } else {
            int x;
            cin >> x;
            --x;
            history[i] = history[version];
            cout << st.get(history[version], x) << endl;
        }
    }
    return 0;
}

