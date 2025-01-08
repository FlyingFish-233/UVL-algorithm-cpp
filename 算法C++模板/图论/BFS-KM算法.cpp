// P6577 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 510;
const long long INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
long long g[NR][NR];

bool vy[NR];
int opp[NR], pre[NR];
long long lx[NR], ly[NR], upd[NR];

void bfs(int s)
{
    memset(pre, 0, sizeof(pre));
    memset(upd, 0x3f, sizeof(upd));
    int now = 0, save = 0; opp[now] = s;
    do {
        int x = opp[now]; vy[now] = true;
        long long delta = INF;
        for (int y = 1; y <= n; y++) if (!vy[y]) {
            if (upd[y] > lx[x] + ly[y] - g[x][y])
                upd[y] = lx[x] + ly[y] - g[x][y], pre[y] = now; // 用匹配边(x,now)更新所有未访问的y的upd
            if (upd[y] < delta) delta = upd[y], save = y; // 从所有未访问的y中选upd最小的(与x无关)
        }
        for (int y = 0; y <= n; y++)
            if (vy[y]) lx[opp[y]] -= delta, ly[y] += delta;
            else upd[y] -= delta;
        now = save;
    } while (opp[now]);
    while (now) opp[now] = opp[pre[now]], now = pre[now];
}

long long km()
{
    for (int i = 1; i <= n; i++)
        memset(vy, false, sizeof(vy)), bfs(i);
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