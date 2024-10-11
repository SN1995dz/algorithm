#include <bits/stdc++.h>

using namespace std;

template<typename T> class SparseTable {
    public:
        SparseTable(const vector<T> &v, function<T(const T &, const T &)> _op=defaultFunc) {
            op = _op;
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) f[i][0] = v[i];
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    f[i][j] = op(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            return op(f[l][k], f[r - (1 << k) + 1][k]);
        }
    private:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        // min;max;gcd;...
        static T defaultFunc(const T &a, const T &b) {
            return max(a, b);
        }

        function<T(const T &, const T &)> op;
};

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

/*
void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}
*/

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n, m;
    // cin >> n >> m;
    n = read(), m = read();
    vector<int> a(n);
    // for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) a[i] = read();
    SparseTable<int> ST(a);
    while (m--) {
        int l, r;
        // cin >> l >> r;
        l = read(), r = read();
        --l, --r;
        // cout << ST.get(l, r) << endl;
        // write(ST.get(l, r));
        // putchar('\n');
        printf("%d\n", ST.get(l, r));
    }
    return 0;
}

