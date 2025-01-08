// P6577 (55 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 510;
const long long INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
long long g[NR][NR];

int opp[NR];
bool vx[NR], vy[NR];
long long lx[NR], ly[NR], upd[NR];

//顶标: lx[i]+ly[j]>=w(i,j)
//相等子图: 二分图中所有满足lx[i]+ly[j]=w(i,j)的边构成的子图
//若相等子图中存在完备匹配, 则这个完备匹配就是二分图的带权最大匹配
bool find(int x)
{
    if (vx[x]) return false;
    vx[x] = true;
    for (int y = 1; y <= n; y++)
        if (lx[x] + ly[y] - g[x][y] == 0) {
            vy[y] = true;
            if (opp[y] == 0 || find(opp[y]))
                { opp[y] = x; return true; }
        }
        else upd[y] = min(upd[y], lx[x] + ly[y] - g[x][y]);
    return false;
}

long long km()
{
    memset(lx, -0x3f, sizeof(lx));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            lx[i] = max(lx[i], g[i][j]);
    for (int i = 1; i <= n; i++)
        while (true) {
            memset(vx, false, sizeof(vx));
            memset(vy, false, sizeof(vy));
            memset(upd, 0x3f, sizeof(upd));
            if (find(i)) break;
            long long delta = INF;
            for (int j = 1; j <= n; j++)
                if (!vy[j]) delta = min(delta, upd[j]);
            for (int j = 1; j <= n; j++) {
                if (vx[j]) lx[j] -= delta;
                if (vy[j]) ly[j] += delta;
            }
        }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += g[opp[i]][i];
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(g, -0x3f, sizeof(g));
    for (int i = 1, x, y; i <= m; i++) {
        long long w;
        scanf("%d%d%lld", &x, &y, &w), g[x][y] = max(g[x][y], w);
    }
    printf("%lld\n", km());
    for (int i = 1; i <= n; i++)
        printf("%d ", opp[i]);
    puts("");
    return 0;
}