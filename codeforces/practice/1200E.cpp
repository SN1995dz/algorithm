#include <bits/stdc++.h>

using namespace std;

const int HASH_CNT = 2;
vector<int> hashBase = {269, 271};
vector<int> hashMod = {int(1e9 + 9), 998244353};

struct StringWithHash {
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
    string s;
    cin >> s;
    StringWithHash a(s);
    for (int i = 1; i < n; ++i) {
        cin >> s;
        StringWithHash b(s);
        int res = 0;
        for (int d = min(s.length(), a.s.length()); d > 0; --d) {
            if (equal(a.getHash(a.s.length() - d, a.s.length() - 1), b.getHash(0, d - 1))) {
                res = d;
                break;
            }    
        }
        for (int j = res; j < (int)s.length(); ++j) a.extend(s[j]);
    }
    cout << a.s << endl;
    return 0;
}

