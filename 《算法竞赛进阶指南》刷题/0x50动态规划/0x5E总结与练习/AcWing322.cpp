# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 210;

int n;
int a[NR];
int f[NR][NR][NR];

int dfs(int l, int r, int pre)
{
    if (f[l][r][pre] != -1) return f[l][r][pre];
    if (l == r) return f[l][r][pre] = (pre + 1) * (pre + 1);
    if (a[l + 1] == a[l]) return f[l][r][pre] = dfs(l + 1, r, pre + 1);
    int ans = dfs(l + 1, r, 0) + (pre + 1) * (pre + 1);
    for (int i = l + 1; i <= r; i++) if (a[i] == a[l] && a[i - 1] != a[l])
        ans = max(ans, dfs(l + 1, i - 1, 0) + dfs(i, r, pre + 1));
    return f[l][r][pre] = ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        memset(f, -1, sizeof(f));
        printf("Case %d: %d\n", t, dfs(1, n, 0));
    }
    return 0;
}