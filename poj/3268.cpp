#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int to, cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const int INF = 1e9;
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
    vector<int> da(n, INF);
    vector<int> db(n, INF);
    da[S] = 0;
    db[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int u = p.second;
        if (da[u] < p.first) continue;
        for (int i = 0; i < (int)Ga[u].size(); ++i) {
            edge e = Ga[u][i];
            int v = e.to;
            if (da[v] > p.first + e.cost) {
                da[v] = p.first + e.cost;
                pq.push(make_pair(da[v], v));
            }
        }
    }
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int u = p.second;
        if (db[u] < p.first) continue;
        for (int i = 0; i < (int)Gb[u].size(); ++i) {
            edge e = Gb[u][i];
            int v = e.to;
            if (db[v] > p.first + e.cost) {
                db[v] = p.first + e.cost;
                pq.push(make_pair(db[v], v));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, da[i] + db[i]);
    }
    cout << ans << endl;
    return 0;
}

