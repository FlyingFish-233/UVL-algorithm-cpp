# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;
const int INF = 0x3f3f3f3f;

int n, m;
int hsz, hx[NR], hy[NR];
int msz, mx[NR], my[NR];

int g[NR][NR];
int opp[NR];
bool vx[NR], vy[NR];
int lx[NR], ly[NR], upd[NR];

bool find(int x)
{
    if (vx[x]) return false;
    vx[x] = true;
    for (int y = 1; y <= hsz; y++)
        if (lx[x] + ly[y] - g[x][y] == 0) {
            vy[y] = true;
            if (opp[y] == 0 || find(opp[y]))
                { opp[y] = x; return true; }
        }
        else upd[y] = min(upd[y], lx[x] + ly[y] - g[x][y]);
    return false;
}

int km()
{
    memset(opp, 0, sizeof(opp));
    memset(lx, -0x3f, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= hsz; i++)
        for (int j = 1; j <= hsz; j++)
            lx[i] = max(lx[i], g[i][j]);
    for (int i = 1; i <= hsz; i++)
        while (true) {
            memset(vx, false, sizeof(vx));
            memset(vy, false, sizeof(vy));
            memset(upd, 0x3f, sizeof(upd));
            if (find(i)) break;
            int delta = INF;
            for (int j = 1; j <= hsz; j++)
                if (!vy[j]) delta = min(delta, upd[j]);
            for (int j = 1; j <= hsz; j++) {
                if (vx[j]) lx[j] -= delta;
                if (vy[j]) ly[j] += delta;
            }
        }
    int ans = 0;
    for (int i = 1; i <= hsz; i++)
        ans += g[opp[i]][i];
    return ans;
}

int main()
{
    while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
        hsz = msz = 0;
        for (int i = 1; i <= n; i++) {
            char s[NR];
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++) {
                if (s[j] == 'H') hx[++hsz] = i, hy[hsz] = j;
                if (s[j] == 'm') mx[++msz] = i, my[msz] = j;
            }
        }
        for (int i = 1; i <= hsz; i++)
            for (int j = 1; j <= hsz; j++)
                g[i][j] = - abs(hx[i] - mx[j]) - abs(hy[i] - my[j]);
        printf("%d\n", -km());
    }
    return 0;
}