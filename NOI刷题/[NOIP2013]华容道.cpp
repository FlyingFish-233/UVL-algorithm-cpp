// P1979 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 32, MR = 1e4 + 10;

int n, m;
int a[NR][NR];

const int nxt[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int dis[NR][NR], q[MR][3];

void bfs(int sx, int sy)
{
    int l = 1, r = 0;
    memset(dis, -1, sizeof(dis)), dis[sx][sy] = 0;
    q[++r][0] = sx, q[r][1] = sy;
    while (l <= r) {
        int x = q[l][0], y = q[l][1]; l++;
        for (int i = 0; i <= 3; i++) {
            int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
            if (a[x0][y0] == 0 || dis[x0][y0] != -1) continue;
            dis[x0][y0] = dis[x][y] + 1;
            q[++r][0] = x0, q[r][1] = y0;
        }
    }
}

int step[NR][NR][4][4], f[NR][NR][4];
bool already[NR][NR][4];

int main()
{
    int T;
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    memset(step, -1, sizeof(step));
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++) if (a[x][y] == 1)
            for (int i = 0; i <= 3; i++) {
                int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
                if (a[x0][y0] == 0) continue;
                a[x][y] = 0, bfs(x0, y0), a[x][y] = 1;
                for (int j = 0; j <= 3; j++) if (j != i)
                    step[x][y][i][j] = dis[x + nxt[j][0]][y + nxt[j][1]];
            }
    while (T--) {
        int ex, ey, sx, sy, tx, ty;
        scanf("%d%d%d%d%d%d", &ex, &ey, &sx, &sy, &tx, &ty);
        if (sx == tx && sy == ty) { printf("0\n"); continue; }
        if (a[sx][sy] == 0) { printf("-1\n"); continue; }
        a[sx][sy] = 0, bfs(ex, ey), a[sx][sy] = 1;
        memset(f, -1, sizeof(f));
        int l = 1, r = 0, ans = 1e9;
        for (int i = 0; i <= 3; i++) {
            f[sx][sy][i] = dis[sx + nxt[i][0]][sy + nxt[i][1]];
            if (f[sx][sy][i] != -1) q[++r][0] = sx, q[r][1] = sy, q[r][2] = i;
        }
        while (l <= r) {
            int x = q[l][0], y = q[l][1], i = q[l][2]; l++;
            int x0 = x + nxt[i][0], y0 = y + nxt[i][1], j;
            already[x][y][i] = false;
            if (x == tx && y == ty) ans = min(ans, f[x][y][i]);
            for (j = 0; j <= 3; j++) if (j != i) {
                int x1 = x + nxt[j][0], y1 = y + nxt[j][1];
                if (step[x][y][i][j] == -1) continue;
                if (f[x][y][j] != -1 && f[x][y][j] <= f[x][y][i] + step[x][y][i][j]) continue;
                f[x][y][j] = f[x][y][i] + step[x][y][i][j];
                if (!already[x][y][j]) already[x][y][j] = true, q[++r][0] = x, q[r][1] = y, q[r][2] = j;
            }
            j = (i + 2) % 4;
            if (f[x0][y0][j] != -1 && f[x0][y0][j] <= f[x][y][i] + 1) continue;
            f[x0][y0][j] = f[x][y][i] + 1;
            if (!already[x0][y0][j]) already[x0][y0][j] = true, q[++r][0] = x0, q[r][1] = y0, q[r][2] = j;
        }
        printf("%d\n", (ans == 1e9) ? -1 : ans);
    }
    return 0;
}

