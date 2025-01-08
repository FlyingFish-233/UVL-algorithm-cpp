# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int MR = (1 << 12) + 10, mod = 1e8;

int n, m, lim;
int a[20];
int f[20][MR];

bool check(int sta)
{
    for (int i = 1; i < m; i++)
        if ((sta >> i & 1) && (sta >> (i - 1) & 1)) return false;
    return true;
}

int dfs(int x, int sta)
{
    if (x > n) return 1;
    if (f[x][sta] != -1) return f[x][sta];
    int save = a[x + 1] & (lim - sta), ans = dfs(x + 1, 0);
    for (int sta0 = save; sta0 > 0; sta0 = (sta0 - 1) & save)
        if (check(sta0)) (ans += dfs(x + 1, sta0)) %= mod;
    return f[x][sta] = ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    lim = (1 << m) - 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0, x; j < m; j++)
            scanf("%d", &x), a[i] |= x << j;
    memset(f, -1, sizeof(f));
    printf("%d\n", dfs(0, 0));
    return 0;
}