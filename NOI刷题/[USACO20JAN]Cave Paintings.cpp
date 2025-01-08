// P6008 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const int PR = 1e9 + 7;

int n, m;
char c[NR][NR];

int fa[NR * NR], cnt[NR * NR];
bool vis[NR * NR];

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y, cnt[y] = 1ll * cnt[x] * cnt[y] % PR;
}

int id(int x, int y)
{
    return (x - 1) * m + y;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", c[i] + 1);
    for (int i = 1; i <= n * m; i++) fa[i] = i, cnt[i] = 1;
    for (int i = n - 1; i >= 2; i--) {
        for (int j = 2; j <= m - 1; j++)  {
            if (c[i][j] == '.' && c[i + 1][j] == '.') merge(id(i, j), id(i + 1, j));
            if (c[i][j] == '.' && c[i][j - 1] == '.') merge(id(i, j), id(i, j - 1));
        }
        for (int j = 2; j <= m; j++) if (c[i][j] == '.') {
            int x = find(id(i, j));
            if (!vis[x]) vis[x] = true, cnt[x]++;
        }
        for (int j = 2; j <= m; j++) if (c[i][j] == '.')
            vis[find(id(i, j))] = false;

    }
    int ans = 1;
    for (int i = 1; i <= n * m; i++)
        if (fa[i] == i) ans = 1ll * ans * cnt[i] % PR;
    printf("%d\n", ans);
    return 0;
}