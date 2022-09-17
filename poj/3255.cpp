#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, S = 0;
    cin >> n >> m;
    vector<edge> G[n];
    while (m--) {
        int x, y, d;
        cin >> x >> y >> d;
        --x, --y;
        G[x].push_back(edge(y, d));
        G[y].push_back(edge(x, d));
    }
    vector<int> d(n, 1e9);
    vector<int> d2(n, 1e9);
    d[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int u = p.second;
        if (d2[u] < p.first) continue;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            edge e = G[u][i];
            int v = e.to;
            if (d[v] > p.first + e.cost) {
                d2[v] = d[v];
                d[v] = p.first + e.cost;
                pq.push(make_pair(d[v], v));
            }
            if (d[v] < p.first + e.cost && d2[v] > p.first + e.cost) {
                d2[v] = p.first + e.cost;
                pq.push(make_pair(d2[v], v));
            }
        }
    }
    cout << d2[n - 1] << endl;
    return 0;
}

