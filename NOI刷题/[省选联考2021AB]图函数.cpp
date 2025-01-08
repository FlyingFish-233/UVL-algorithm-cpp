// P7516 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 2e5 + 10;

int n, m;
int f[NR][NR]; // 加入边f[i][j]时i->j连通
int d[MR], h[MR];

// f(i, G)中 j被删去 <=> 删去1~j-1后i<->j (i > j)
// h(G)表示这样的(i, j)数量, d(G[t])表示G[t+1]加上t这条边后增加的(i, j)数量
// 枚举所有点对，看它们何时加入到图G中
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), f[x][y] = i;
    for (int k = n; k >= 1; k--) {
        for (int i = k + 1; i <= n; i++) d[min(f[i][k], f[k][i])]++;
        for (int i = 1; i <= n; i++) if (f[i][k])
            for (int j = 1; j <= ((i > k) ? k - 1 : n); j++) // 不需要再去考虑两个>=k的点之间的连通性
                f[i][j] = max(f[i][j], min(f[i][k], f[k][j]));
    }
    h[m + 1] = n; // (i, i)有n对
    for (int i = m; i >= 1; i--)
        h[i] = h[i + 1] + d[i];
    for (int i = 1; i <= m + 1; i++)
        printf("%d ", h[i]);
    return 0;
}

