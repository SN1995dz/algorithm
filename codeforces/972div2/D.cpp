#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        vector<int> b(n + 1);
        vector<int> pa(n + 1, 0);
        vector<int> pb(n + 1, 0);
        vector<pair<int, int>> cpa;
        vector<pair<int, int>> cpb;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pa[i] = __gcd(pa[i - 1], a[i]);
            if (i == n || pa[i] != pa[i - 1]) cpa.push_back(make_pair(pa[i], i));
        }
        for (int i = 1; i <= n; ++i) {
            cin >> b[i];
            pb[i] = __gcd(pb[i - 1], b[i]);
            if (i == n || pb[i] != pb[i - 1]) cpb.push_back(make_pair(pb[i], i));
        }
        vector<int> sa(n + 2, 0);
        vector<int> sb(n + 2, 0);
        for (int i = n; i >= 1; --i) {
            sa[i] = __gcd(sa[i + 1], a[i]);
            sb[i] = __gcd(sb[i + 1], b[i]);
        }
        int ans = 0;
        long long num = -1;
        vector<pair<int, int>> cma;
        vector<pair<int, int>> cmb;
        for (int r = 1; r <= n; ++r) {
            for (int i = 0; i < (int)cma.size(); ++i) cma[i].first = __gcd(cma[i].first, a[r]);
            for (int i = 0; i < (int)cmb.size(); ++i) cmb[i].first = __gcd(cmb[i].first, b[r]);
            cma.push_back(make_pair(a[r], r));
            cmb.push_back(make_pair(b[r], r));
            int j = 0;
            for (int i = 1; i < (int)cma.size(); ++i) {
                if (cma[j].first == cma[i].first) cma[j] = cma[i];
                else cma[++j] = cma[i];
            }
            cma.resize(j + 1);
            j = 0;
            for (int i = 1; i < (int)cmb.size(); ++i) {
                if (cmb[j].first == cmb[i].first) cmb[j] = cmb[i];
                else cmb[++j] = cmb[i];
            }
            cmb.resize(j + 1);
            int ipa = 0, ipb = 0, ima = 0, imb = 0, last = 0;
            while (true) {
                int l = min({cpa[ipa].second, cpb[ipb].second, cma[ima].second, cmb[imb].second});
                int res = __gcd(__gcd(pa[l - 1], cmb[imb].first), sa[r + 1]) + __gcd(__gcd(pb[l - 1], cma[ima].first), sb[r + 1]);
                if (res > ans) {
                    ans = res;
                    num = l - last;
                } else if (res == ans) {
                    num += l - last;
                }
                if (l == r) break;
                last = l;
                if (l == cpa[ipa].second) ++ipa;
                if (l == cpb[ipb].second) ++ipb;
                if (l == cma[ima].second) ++ima;
                if (l == cmb[imb].second) ++imb;
            }
        }
        cout << ans << " " << num << endl;
    }
    return 0;
}

