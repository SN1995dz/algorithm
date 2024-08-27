#include <bits/stdc++.h>

using namespace std;

class StringWithHash {
    public:
        string s;

        explicit StringWithHash() : powMod(HASH_CNT, vector<int>(1, 1)), hash(HASH_CNT, vector<int>(1, 0)) {}

        explicit StringWithHash(string _s) : powMod(HASH_CNT, vector<int>(1, 1)), hash(HASH_CNT, vector<int>(1, 0)) {
            for (auto c : _s) extend(c);
        }

        void extend(char c) {
            s.push_back(c);
            for (int i = 0; i < HASH_CNT; ++i) {
                powMod[i].push_back((long long)powMod[i].back() * hashBase[i] % hashMod[i]);
                hash[i].push_back(((long long)hash[i].back() * hashBase[i] + c) % hashMod[i]);
            }
        }

        vector<int> getHash(int l, int r) {
            assert(0 <= l && l <= r && r < (int)s.length());
            vector<int> res;
            for (int i = 0; i < HASH_CNT; ++i) {
                res.push_back((hash[i][r + 1] + hashMod[i] - (long long)hash[i][l] * powMod[i][r - l + 1] % hashMod[i]) % hashMod[i]);
            }
            return res;
        }

    private:
        const int HASH_CNT = 2;
        vector<int> hashBase = {269, 271};
        vector<int> hashMod = {int(1e9 + 9), 998244353};
        vector<vector<int>> powMod;
        vector<vector<int>> hash;
};

bool equal(const vector<int> &a, const vector<int> &b) {
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> S;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        StringWithHash a(s);
        auto tmp = a.getHash(0, s.length() - 1);
        S.push_back(make_pair(tmp[0], tmp[1]));
    }
    sort(S.begin(), S.end());
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        if (S[i - 1] != S[i]) ++ans;
    }
    cout << ans << endl;
    return 0;
}

