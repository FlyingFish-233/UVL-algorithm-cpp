# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>
 
using namespace std;

const int NR = 20;
const int INF = 0x3f3f3f3f;

int n, m;
bool vis[NR][NR][2];
int f[NR][NR][2];
/*
n个人和n个鬼，船上的人鬼总数需在1到m之间，河岸和船上人的个数都得大于等于鬼的个数（否则会被吃）
问：从西岸把所有人鬼送到东岸最少需要摆渡多少次
 (x,y,k)表示东岸x个人和y个鬼，k为船当前在西/东案
 x == 0 || x == n || x == y为合法状态
 */

int dfs(int x, int y, int k)
{
    if (f[x][y][k] != INF) return f[x][y][k];
    if (vis[x][y][k]) return INF;
    vis[x][y][k] = true;
    int ret = INF;
    for (int k1 = 0; k1 <= m; k1++)
        for (int k2 = 0; k2 <= m; k2++) if (k1 + k2 > 0 && k1 + k2 <= m && (k1 == 0 || k1 >= k2)) {
            int x0, y0, k0 = !k;
            if (k == 0) x0 = x + k1, y0 = y + k2;
            if (k == 1) x0 = x - k1, y0 = y - k2;
            if (x0 < 0 || x0 > n || y0 < 0 || y0 > n) continue;
            if (x0 == 0 || x0 == n || x0 == y0) ret = min(ret, dfs(x0, y0, k0) + 1);
        }
    vis[x][y][k] = false;
    return f[x][y][k] = ret;
}


int main()
{
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f)), f[n][n][1] = 0;
    int ans = dfs(0, 0, 0);
    printf("%d\n", (ans == INF) ? -1 : ans);
    return 0;
}