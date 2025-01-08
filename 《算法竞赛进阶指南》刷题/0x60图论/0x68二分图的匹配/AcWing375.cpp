# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;
const double eps = 1e-8;

int n;
int a[NR], b[NR], c[NR], d[NR];
double g[NR][NR];

int opp[NR];
bool vx[NR], vy[NR];
double lx[NR], ly[NR], upd[NR];

bool find(int x)
{
    if (vx[x]) return false;
    vx[x] = true;
    for (int y = 1; y <= n; y++)
        if (fabs(lx[x] + ly[y] - g[x][y]) < eps) {
            vy[y] = true;
            if (opp[y] == 0 || find(opp[y]))
                { opp[y] = x; return true; }
        }
        else upd[y] = min(upd[y], lx[x] + ly[y] - g[x][y]);
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &c[i], &d[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i], &b[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            g[i][j] = -sqrt((a[i] - c[j]) * (a[i] - c[j]) + (b[i] - d[j]) * (b[i] - d[j]));
    fill(lx + 1, lx + n + 1, -1e9);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            lx[i] = max(lx[i], g[i][j]);
    for (int i = 1; i <= n; i++)
        while (true) {
            memset(vx, false, sizeof(vx));
            memset(vy, false, sizeof(vy));
            fill(upd + 1, upd + n + 1, 1e9);
            if (find(i)) break;
            double delta = 1e9;
            for (int j = 1; j <= n; j++)
                if (!vy[j]) delta = min(delta, upd[j]);
            for (int j = 1; j <= n; j++) {
                if (vx[j]) lx[j] -= delta;
                if (vy[j]) ly[j] += delta;
            }
        }
    for (int i = 1; i <= n; i++)
        printf("%d\n", opp[i]);
    return 0;
}