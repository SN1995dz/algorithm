#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

const int INF = 1e9;

vector<int> dijkstra(int n, int S, vector<vector<edge> > &G) {
    vector<int> d(n, INF);
    d[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int u = p.second;
        if (d[u] < p.first) continue;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            edge e = G[u][i];
            int v = e.to;
            if (d[v] > p.first + e.cost) {
                d[v] = p.first + e.cost;
                pq.push(make_pair(d[v], v));
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, S;
    cin >> n >> m >> S;
    --S;
    vector<vector<edge> > Ga(n);
    vector<vector<edge> > Gb(n);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        Ga[x].push_back(edge(y, z));
        Gb[y].push_back(edge(x, z));
    }
    vector<int> da = dijkstra(n, S, Ga);
    vector<int> db = dijkstra(n, S, Gb);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, da[i] + db[i]);
    }
    cout << ans << endl;
    return 0;
}

