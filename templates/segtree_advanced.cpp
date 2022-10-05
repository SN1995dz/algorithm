#include <bits/stdc++.h>

using namespace std;

void PushUp(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void build(int rt, int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) >> 1;
    build(rt << 1, l, m);
    build(rt << 1 | 1, m + 1, r);
    PushUp(rt);
}

void update(int p, int v, int rt, int l, int r) {
    if (l == r) {
        sum[rt] += v;
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p, v, rt << 1, l, m);
    else update(p, v, rt << 1 | 1, m + 1, r);
    PushUp(rt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    return 0;
}

