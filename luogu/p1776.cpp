#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, W;
    cin >> n >> W;
    vector<int> f(W + 1);
    vector<pair<int, int>> deq(W);
    for (int i = 0; i < n; ++i) {
        int v, w, m;
        cin >> v >> w >> m;
        for (int j = 0; j < w; ++j) {
            if (j >= W) break;
            int S = W - j, T = (W - j) / w;
            int head = 0, tail = -1;
            for (int k = 1; k <= m && k <= T; ++k) {
                while (head <= tail && deq[tail].first < f[S - k * w] + k * v) --tail;
                deq[++tail] = make_pair(f[S - k * w] + k * v, k);
            }
            f[S] = max(f[S], deq[head].first);
            int offset = 0;
            for (int k = m + 1, p = S - w, q = 1; q < T; p -= w, ++q) {
                if (k <= T) {
                    while (head <= tail && deq[tail].first < f[S - k * w] + k * v) --tail;
                    deq[++tail] = make_pair(f[S - k * w] + k * v, k);
                    ++k;
                }
                while (head <= tail && deq[head].second <= q) ++head;
                offset -= v;
                f[p] = max(f[p], deq[head].first + offset);
            }
        }
    }
    cout << f[W] << endl;
    return 0;
}

