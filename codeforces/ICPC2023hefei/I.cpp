#include <bits/stdc++.h>
 
using namespace std;
 
 
int calc(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    return c - 'A' + 26;
 
}
 
void print(vector<int> ta) {
    for (int i = 0; i < (int)ta.size(); ++i) {
        if (ta[i] < 26) cout << char('a' + ta[i]);
        else cout << char('A' + ta[i] - 26);
    }
    cout << endl;
}
 
bool check(vector<int> a, vector<string> ans) {
    int n = a.size();
    vector<string> res;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int hi = i * j / n, lo = i * j % n;
            string tmp = "";
            if (hi > 0) {
                if (a[hi] < 26) tmp.push_back(a[hi] + 'a');
                else tmp.push_back(a[hi] + 'A' - 26);
            }
            if (a[lo] < 26) tmp.push_back(a[lo] + 'a');
            else tmp.push_back(a[lo] + 'A' - 26);
            res.push_back(tmp);
        }
    }
    sort(res.begin(), res.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (ans[i] != res[i]) return false;
    }
    return true;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> xx(n, 0);
        vector<int> yy(n, 0);
        vector<int> zz(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i * j / n > 0) {
                    ++xx[i * j / n];
                    ++yy[i * j % n];
                } else {
                    ++zz[i * j % n];
                }
            }
        }
        map<pair<pair<int, int>, int>, vector<int>> M;
        for (int i = 0; i < n; ++i) {
            M[make_pair(make_pair(xx[i], yy[i]), zz[i])].push_back(i);
        }
        vector<int> na, nb;
        for (auto &kv : M) {
            if (kv.second.size() > 1) {
                for (auto & v : kv.second) {
                    na.push_back(v);
                }
            }
        }
        vector<string> a;
        vector<int> x(n, 0);
        vector<int> y(n, 0);
        vector<int> z(n, 0);
        for (int i = 0; i < n * n; ++i) {
            string s;
            cin >> s;
            a.push_back(s);
            if (s.length() == 2) {
                ++x[calc(s[0])];
                ++y[calc(s[1])];
            } else {
                ++z[calc(s[0])];
            }
        }
        sort(a.begin(), a.end());
        vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i) {
            auto &tmp = M[make_pair(make_pair(x[i], y[i]), z[i])];
            if (tmp.size() == 1) {
                ans[tmp[0]] = i; 
            } else {
                if (tmp.size() == 0) continue;
                nb.push_back(i);
            }
        }
        do {
            vector<int> n_ans(n, -1);
            for (int i = 0; i < (int)nb.size(); ++i) {
                n_ans[na[i]] = nb[i];
            }
            for (int i = 0; i < n; ++i) {
                if (ans[i] != -1) n_ans[i] = ans[i];
            }
            if (check(n_ans, a)) {
                for (int i = 0; i < n; ++i) ans[i] = n_ans[i];
                break;
            }
        } while (next_permutation(nb.begin(), nb.end()));
        print(ans);
    }
    return 0;
}

