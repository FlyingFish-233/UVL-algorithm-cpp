// P1514 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 510;

struct Array
{
    int l, r;
    Array() { l = 1e9, r = 0; }
    bool operator < (const Array &cmp) const {
        return l < cmp.l;
    }
};

int n, m;
int a[NR][NR];

const int nxt[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int q[NR * NR][2];
bool vis[NR][NR], flag[NR];
Array b[NR];

void bfs(int s)
{
    memset(vis, false, sizeof(vis));
    int l = 1, r = 0;
    q[++r][0] = 1, q[r][1] = s, vis[1][s] = true;
    while (l <= r) {
        int x = q[l][0], y = q[l][1]; l++;
        if (x == n) flag[y] = true, b[s].l = min(b[s].l, y), b[s].r = max(b[s].r, y);
        for (int i = 0; i <= 3; i++) {
            int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
            if (x0 < 1 || x0 > n || y0 < 1 || y0 > m) continue;
            if (vis[x0][y0] || a[x0][y0] >= a[x][y]) continue;
            vis[x0][y0] = true, q[++r][0] = x0, q[r][1] = y0;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; i++)
        bfs(i);
    int tmp = 0;
    for (int i = 1; i <= m; i++)
        if (!flag[i]) tmp++;
    if (tmp > 0) return printf("0\n%d\n", tmp), 0;
    sort(b + 1, b + m + 1);
    int R = 0, r_max = 0, cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (b[i].l == 1e9) break;
        if (b[i].l <= R + 1) r_max = max(r_max, b[i].r);
        else R = r_max, r_max = b[i].r, cnt++;
    }
    if (R < m) cnt++;
    printf("1\n%d\n", cnt);
    return 0;
}

