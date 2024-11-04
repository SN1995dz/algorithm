#include <bits/stdc++.h>

using namespace std;

const int N = 2000000;

/*
struct node {
    node() {
        val = 0;
        lazy = 0;
        next[0] = next[1] = 0;
    }

    long long val;
    long long lazy;
    int next[2];
};

node pool[2000000];*/

long long val[N], lazy[N];
int lson[N], rson[N];

int rt[100005];

int cnt;

/*int newNode() {
    ++cnt;
    return cnt;
}*/

void build(int x, int l, int r, int *v) {
    // pool[x].lazy = 0;    
    lazy[x] = 0;
    if (l == r) {
        // pool[x].val = v[l];
        val[x] = v[l];
        return;
    }
    int y = (l + r) >> 1;
    // pool[x].next[0] = newNode();
    // pool[x].next[1] = newNode();
    // lson[x] = newNode();
    // rson[x] = newNode();
    lson[x] = ++cnt;
    rson[x] = ++cnt;
    // build(pool[x].next[0], l, y, v);
    // build(pool[x].next[1], y + 1, r, v);
    build(lson[x], l, y, v);
    build(rson[x], y + 1, r, v);
    // pool[x].val = pool[pool[x].next[0]].val + pool[pool[x].next[1]].val;
    val[x] = val[lson[x]] + val[rson[x]];
}

void modify(int x, int u, int l, int r, int ll, int rr, const int &v) {
    // pool[u] = pool[x];
    val[u] = val[x];
    lazy[u] = lazy[x];
    lson[u] = lson[x];
    rson[u] = rson[x];
    if (ll <= l && r <= rr) {
        // pool[u].lazy += v;
        lazy[u] += v;
        return;
    }
    int y = (l + r) >> 1;
    if (ll <= y) {
        // pool[u].next[0] = newNode();
        // modify(pool[x].next[0], pool[u].next[0], l, y, ll, rr, v);
        // lson[u] = newNode();
        lson[u] = ++cnt;
        modify(lson[x], lson[u], l, y, ll, rr, v);
    }
    if (rr > y) {
        // pool[u].next[1] = newNode();
        // modify(pool[x].next[1], pool[u].next[1], y + 1, r, ll, rr, v);
        // rson[u] = newNode();
        rson[u] = ++cnt;
        modify(rson[x], rson[u], y + 1, r, ll, rr, v);
    }
    // pool[u].val += v * (min(rr, r) - max(ll, l) + 1);
    val[u] += v * (min(rr, r) - max(ll, l) + 1);
}

long long query(int x, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) {
        // return pool[x].val + pool[x].lazy * (r - l + 1);
        return val[x] + lazy[x] * (r - l + 1);
    }
    int y = (l + r) >> 1;
    // long long res = pool[x].lazy * (min(rr, r) - max(ll, l) + 1);
    long long res = lazy[x] * (min(rr, r) - max(ll, l) + 1);
    // if (ll <= y) res += query(pool[x].next[0], l, y, ll, rr);
    // if (rr > y) res += query(pool[x].next[1], y + 1, r, ll, rr);
    if (ll <= y) res += query(lson[x], l, y, ll, rr);
    if (rr > y) res += query(rson[x], y + 1, r, ll, rr);
    return res;
}

int a[100005];

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n, m;
    // while (cin >> n >> m) {
    while (scanf("%d%d", &n, &m) != EOF) {
        // for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        cnt = 1;
        rt[0] = 1;
        build(rt[0], 0, n - 1, a);
        int curTime = 0;
        char op[10];
        while (m--) {
            // string op;
            // cin >> op;
            scanf("%s", op);
            if (op[0] == 'C') {
                int l, r, d;
                // cin >> l >> r >> d;
                scanf("%d%d%d", &l, &r, &d);
                --l, --r;
                // rt[++curTime] = newNode();
                rt[++curTime] = ++cnt;
                modify(rt[curTime - 1], rt[curTime], 0, n - 1, l, r, d);
            } else if (op[0] == 'Q') {
                int l, r;
                // cin >> l >> r;
                scanf("%d%d", &l, &r);
                --l, --r;
                // cout << query(rt[curTime], 0, n - 1, l, r) << endl;
                printf("%lld\n", query(rt[curTime], 0, n - 1, l, r));
            } else if (op[0] == 'H') {
                int l, r, t;
                // cin >> l >> r >> t;
                scanf("%d%d%d", &l, &r, &t);
                --l, --r;
                // cout << query(rt[t], 0, n - 1, l, r) << endl;
                printf("%lld\n", query(rt[t], 0, n - 1, l, r));
            } else {
                int t;
                // cin >> t;
                scanf("%d", &t);
                curTime = t;
            }
        }
    }
    return 0;
}

