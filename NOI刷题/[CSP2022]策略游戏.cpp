// P8818 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 1e9 + 10;

struct ST
{
    int len, a[NR];
    int f[NR][20], g[NR][20];

    void init()
    {
        for (int i = 1; i <= len; i++)
            if (a[i] == INF) f[i][0] = -INF, g[i][0] = INF;
            else f[i][0] = g[i][0] = a[i];
        for (int j = 1; (1 << j) <= len; j++)
            for (int i = 1; i + (1 << j) - 1 <= len; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                g[i][j] = min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
            }
    }

    int q_max(int l, int r)
    {
        int k = log2(r - l + 1);
        return max(f[l][k], f[r - (1 << k) + 1][k]);
    }

    int q_min(int l, int r)
    {
        int k = log2(r - l + 1);
        return min(g[l][k], g[r - (1 << k) + 1][k]);
    }
};

int n, m, T;
ST A1, A2, B;

int main()
{
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        if (x >= 0) A1.a[i] = x, A2.a[i] = INF;
        else A1.a[i] = INF, A2.a[i] = x;
    }
    for (int i = 1; i <= m; i++)
        scanf("%d", &B.a[i]);
    A1.len = A2.len = n, B.len = m;
    A1.init(), A2.init(), B.init();
    while (T--) {
        int l1, r1, l2, r2, t[4];
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        t[0] = A1.q_max(l1, r1), t[1] = A1.q_min(l1, r1);
        t[2] = A2.q_max(l1, r1), t[3] = A2.q_min(l1, r1);
        int b1 = B.q_max(l2, r2), b2 = B.q_min(l2, r2);
        long long ans = -1e18;
        for (int i = 0; i <= 3; i++) if (t[i] != INF && t[i] != -INF)
            ans = max(ans, min(1ll * t[i] * b1, 1ll * t[i] * b2));
        printf("%lld\n", ans);
    }
    return 0;
}