#include <bits/stdc++.h>

using namespace std;

unsigned int X, Y, Z;

unsigned int RNG61() {
    X = X ^ (X << 11);
    X = X ^ (X >> 4);
    X = X ^ (X << 5);
    X = X ^ (X >> 14);
    unsigned int W = X ^ (Y ^ Z);
    X = Y;
    Y = Z;
    Z = W;
    return Z;
}

template<typename T> class SegTree {
    public:
        SegTree(int _n) : n(_n) {
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1);
        }
        
        void modify(int ll, int rr, const T &v) {
            modify(0, 0, n - 1, ll, rr, v);
        }

        void query(long long &res) {
            query(0, 0, n - 1, res);
        }
    private:
        struct node {
            T val = T();

            void apply(int l, int r, T v) {
                val = max(val, v);
            }
        };
        
        int n;
        vector<node> tree;

        inline void push(int x, int l, int r) {
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            tree[x + 1].apply(l, y, tree[x].val);
            tree[z].apply(y + 1, r, tree[x].val);
        }

        void build(int x, int l, int r) {
            if (l == r) return;
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            build(x + 1, l, y);
            build(z, y + 1, r);
        }

        void modify(int x, int l, int r, int ll, int rr, const T &v) {
            if (tree[x].val >= v) return;
            if (ll <= l && r <= rr) {
                tree[x].apply(l, r, v);
                return;
            }
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            push(x, l, r);
            if (ll <= y) modify(x + 1, l, y, ll, rr, v);
            if (rr > y) modify(z, y + 1, r, ll, rr, v);
        }
        
        void query(int x, int l, int r, long long &res) {
            if (l == r) {
                res ^= (long long)(l + 1) * tree[x].val;
                return;
            }
            int y = (l + r) >> 1;
            int z = x + ((y - l + 1) << 1);
            push(x, l, r);
            query(x + 1, l, y, res);
            query(z, y + 1, r, res);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m >> X >> Y >> Z;
        SegTree<int> st(n);
        while (m--) {
            int l = RNG61() % n;
            int r = RNG61() % n;
            if (l > r) swap(l, r);
            int v = RNG61() % (1 << 30);
            st.modify(l, r, v);
        }
        long long ans = 0;
        st.query(ans);
        cout << ans << endl;
    }
    return 0;
}

