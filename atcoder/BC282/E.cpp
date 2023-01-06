#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

// @param m '1 <= m'
// @return x mod m
long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// @param n '0 <= n'
// @param m '1 <= m'
// @return '(x ** n) % m'
long long pow_mod(long long x, long long n, int m) {
    assert(0 <= n && 1 <= m);
    if (m == 1) return 0;
    long long r = 1, y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = r * y % m;
        y = y * y % m;
        n >>= 1;
    }
    return r;
}

long long floor_div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && a % b != 0);
}

vector<int> calc(int n, int MOD) {
    vector<int> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    return inv;
}

vector<int> spf; // spf[x] i s the smallest prime factor of number x, where x >= 2

void sieve(int n) { // O(Nlog(logN)) ~ O(N)
    spf.resize(n + 1);
    for (int i = 2; i <= n; ++i) spf[i] = i;
    for (int i = 2; i * i <= n; ++i) {
        if (spf[i] != i) continue; // skip if 'i' is not a prime number
        for (int j = i * i; j <= n; j += i) {
            if (spf[j] > i) spf[j] = i; // update to the smallest prime factor of j
        }
    }
}

vector<int> getPrimeFactors(int n) { // O(logN)
    vector<int> factors;
    while (n > 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}

struct dsu {
    public:
        dsu() : _n(0) {}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

        bool same(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return leader(a) == leader(b);
        }

        int leader(int a) {
            assert(0 <= a && a < _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

        vector<vector<int>> groups() {
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; ++i) {
                leader_buf[i] = leader(i);
                ++group_size[leader_buf[i]];
            }
            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; ++i) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; ++i) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
            return result;
        }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back(make_pair((pow_mod(a[i], a[j], m) + pow_mod(a[j], a[i], m)) % m, make_pair(i, j)));
        }
    }
    sort(edges.rbegin(), edges.rend());
    long long ans = 0;
    dsu d(n);
    int cnt = 0;
    for (auto &e : edges) {
        auto [x, y] = e.second;
        if (!d.same(x, y)) {
            ++cnt;
            d.merge(x, y);
            ans += e.first;
        }
        if (cnt == n - 1) break;
    }
    cout << ans << endl;
    return 0;
}

