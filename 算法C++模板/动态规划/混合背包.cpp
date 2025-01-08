// AcWing7 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 1e3 + 10;

int n, m;
int w[NR], v[NR], c[NR];
int f[MR];

void ZeroOnePack(int W, int V)
{
    for (int j = m; j >= W; j--)
        f[j] = max(f[j], f[j - W] + V);
}

void CompletePack(int W, int V)
{
    for (int j = W; j <= m; j++)
        f[j] = max(f[j], f[j - W] + V);
}

void MultiplePack(int W, int V, int C)
{
    if (C * W > m) { CompletePack(W, V); return; }
    for (int i = 1; i < C; C -= i, i <<= 1)
        ZeroOnePack(i * W, i * V);
    ZeroOnePack(C * W, C * V);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &w[i], &v[i], &c[i]);
    memset(f, -0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (c[i] == -1) ZeroOnePack(w[i], v[i]);
        if (c[i] == 0) CompletePack(w[i], v[i]);
        if (c[i] > 0) MultiplePack(w[i], v[i], c[i]);
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}