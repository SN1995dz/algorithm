#include <bits/stdc++.h>

using namespace std;

struct BipartiteGraph {
    public:
        // left: n, 0~n-1; right: m, n~n+m-1 
        explicit BipartiteGraph(int _n, int _m) : n(_n), m(_m), G(_n + _m), visited(_m) {
            match.resize(_m, -1);
        }
        
        void addEdge(int u, int v) {
            assert(0 <= u && u < n);
            assert(n <= v && v < n + m);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        bool agumentPath(int u) {
            for (int i = 0; i < (int)G[u].size(); ++i) {
                int v = G[u][i];
                if (visited[v - n]) continue;
                visited[v - n] = true;
                if (match[v - n] == -1 || agumentPath(match[v - n])) {
                    match[v - n] = u;
                    return true;
                }
            }
            return false;
        }

        int maximumMatching() {
            int res = 0;
            for (int i = 0; i < n; ++i) {
                fill(visited.begin(), visited.end(), false);
                if (agumentPath(i)) ++res;
            }
            return res;
        }

    private:
        int n, m;
        vector<vector<int>> G;
        vector<bool> visited;
        vector<int> match;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        BipartiteGraph g(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int c;
                cin >> c;
                if (c == 1) {
                    g.addEdge(i, n + j);
                }
            }
        }
        if (g.maximumMatching() == n) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

