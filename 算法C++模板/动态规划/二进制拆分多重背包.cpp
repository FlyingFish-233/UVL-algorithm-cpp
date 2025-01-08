// AcWing4 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e4 + 10, MR = 2e3 + 10;

int n, m;
int tmp, w[NR], v[NR];
int f[MR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, a, b, c; i <= n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        for (int j = 1; j <= c; c -= j, j <<= 1)
            w[++tmp] = a * j, v[tmp] = b * j;
        if (c > 0) w[++tmp] = a * c, v[tmp] = b * c;
    }
    n = tmp, memset(f, -0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--)
            f[j] = max(f[j], f[j - w[i]] + v[i]);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}