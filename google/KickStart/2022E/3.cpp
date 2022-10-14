#include <bits/stdc++.h>

using namespace std;

struct state {
    int x, y, m, p;
    long long c;
    state(int _x, int _y, int _m, int _p, long long _c) : x(_x), y(_y), m(_m), p(_p), c(_c) {}

    friend bool operator < (const state &a, const state &b) {
        return a.c < b.c;
    }
};

long long floor_div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && a % b != 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    const long long INF = 1e18;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int N, P, M, R, C;
        cin >> N >> P >> M >> R >> C;
        --R, --C;
        vector<string> OP(4);
        vector<int> K(4);
        for (int i = 0; i < 4; ++i) {
            cin >> OP[i] >> K[i];
        }
        vector<vector<pair<int, int>>> map(N, vector<pair<int, int>>(N, make_pair(0, -1)));
        for (int i = 0; i < P; ++i) {
            int x, y, c;
            cin >> x >> y >> c;
            --x, --y;
            map[x][y] = make_pair(c, i);
        }
        auto calc = [&](int i, long long v) {
            if (OP[i][0] == '+') return v + K[i];
            if (OP[i][0] == '-') return v - K[i];
            if (OP[i][0] == '*') return v * K[i];
            return floor_div(v, K[i]);
        };
        const int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, 1, -1, 0};
        long long ans = -INF;
        vector<vector<vector<vector<long long>>>> f(N, vector<vector<vector<long long>>>(N, vector<vector<long long>>(M + 1, vector<long long>(1 << P, -INF))));
        f[R][C][0][0] = 0;
        priority_queue<state> Q;
        Q.push(state(R, C, 0, 0, 0));
        while (!Q.empty()) {
            auto e = Q.top();
            Q.pop();
            if (e.c != f[e.x][e.y][e.m][e.p]) continue;
            if (e.p == (1 << P) - 1) {
                ans = max(ans, e.c);
            }
            if (e.m == M) continue;
            int nm = e.m + 1;
            if (e.c > f[e.x][e.y][nm][e.p]) {
                f[e.x][e.y][nm][e.p] = e.c;
                Q.push(state(e.x, e.y, nm, e.p, e.c));
            }
            for (int i = 0; i < 4; ++i) {
                int nx = e.x + dx[i], ny = e.y + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                long long tmp = calc(i, e.c);
                if (tmp > f[nx][ny][nm][e.p]) {
                    f[nx][ny][nm][e.p] = tmp;
                    Q.push(state(nx, ny, nm, e.p, tmp));
                }
                if (map[nx][ny].first && (e.p >> map[nx][ny].second & 1) == 0) {
                    int nmask = e.p | (1 << map[nx][ny].second);
                    if (tmp + map[nx][ny].first > f[nx][ny][nm][nmask]) {
                        f[nx][ny][nm][nmask] = tmp + map[nx][ny].first;
                        Q.push(state(nx, ny, nm, nmask, f[nx][ny][nm][nmask]));
                    }
                }
            }
        }
        if (ans == -INF) cout << "IMPOSSIBLE" << endl;
        else cout << ans << endl;
    }
    return 0;
}

