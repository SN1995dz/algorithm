#include <bits/stdc++.h>

using namespace std;

template<typename T> class sparse_table {
    public:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        sparse_table(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) f[i][0] = v[i];
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    //min or max
                    f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            //min or max
            return max(f[l][k], f[r - (1 << k) + 1][k]);
        }
};

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    int n, m;
    //cin >> n >> m;
    n = read(), m = read();
    vector<int> a(n);
    //for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) a[i] = read();
    sparse_table<int> st(a);
    while (m--) {
        int l, r;
        //cin >> l >> r;
        l = read(), r = read();
        --l, --r;
        //cout << st.get(l, r) << endl;
        printf("%d\n", st.get(l, r));
    }
    return 0;
}

