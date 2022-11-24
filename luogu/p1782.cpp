#include <bits/stdc++.h>

using namespace std;

// need O2

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, C;
    cin >> n >> m >> C;
    vector<long long> f(C + 1, 0);
    vector<pair<long long, int>> deq(C);
    for (int i = 0; i < n; ++i) {
        int v, w, d;
        cin >> v >> w >> d;
        /*int k = 1;
        while (k <= d) {
            for (int j = C; j >= k * v; --j) {
                f[j] = max(f[j], f[j - k * v] + k * w);
            }
            d -= k;
            k *= 2;
        }
        if (d) {
            for (int j = C; j >= d * v; --j) {
                f[j] = max(f[j], f[j - d * v] + d * w);
            }
        }*/
        for (int j = 0; j < v; ++j) {
            if (j >= C) break;
            int S = C - j, T = (C - j) / v;
            int head = 0, tail = -1;
            for (int k = 1; k <= d && k <= T; ++k) {
                while (head <= tail && deq[tail].first < f[S - k * v] + k * w) --tail;
                deq[++tail] = make_pair(f[S - k * v] + k * w, k);
            }
            f[S] = max(f[S], deq[head].first);
            int offset = 0;
            for (int k = d + 1, p = S - v, q = 1; q < T; p -= v, ++q) {
                if (k <= T) {
                    while (head <= tail && deq[tail].first < f[S - k * v] + k * w) --tail;
                    deq[++tail] = make_pair(f[S - k * v] + k * w, k);
                    ++k;
                }
                while (head <= tail && deq[head].second <= q) ++head;
                offset -= w;
                f[p] = max(f[p], deq[head].first + offset);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = C; j >= 0; --j) {
            for (int k = 0; k <= j; ++k) {
                f[j] = max(f[j], f[j - k] + (long long)a * k * k + b * k + c);
            }
        }
    }
    cout << f[C] << endl;
    return 0;
}

