// CF364E (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2500 + 10;

int n, m, k;
char c[NR][NR];
int s[NR][NR];
int up[10], down[10];
long long ans;

int calc(int x1, int y1, int x2, int y2)
{
    return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
}

void dfs(int x1, int y1, int x2, int y2, bool flag)
{
    if (x1 >= x2 || y1 >= y2) return;
    if (x2 - x1 == 1 && y2 - y1 == 1) { ans += (calc(x1, y1, x2, y2) == k); return; }
    if (flag) {
        int mid = (x1 + x2) / 2;
        dfs(x1, y1, mid, y2, !flag), dfs(mid, y1, x2, y2, !flag);
        for (int i = y1; i < y2; i++) {
            up[0] = down[0] = mid;
            for (int t = 1; t <= k + 1; t++)
                up[t] = x1, down[t] = x2;
            for (int j = i + 1; j <= y2; j++) {
                for (int t = 1; t <= k + 1; t++) {
                    while (calc(up[t], i, mid, j) >= t) up[t]++;
                    // up[t]表示使矩形(x + 1, i + 1, mid, j)中1的个数小于t的最大x
                    while (calc(mid, i, down[t], j) >= t) down[t]--;
                    // down[t]表示使矩形(mid + 1, i + 1, x, j)中1的个数小于t的最小x
                }
                for (int t = 0; t <= k; t++)
                    ans += (up[t] - up[t + 1]) * (down[k - t + 1] - down[k - t]);
            }
        }
    }
    else {
        int mid = (y1 + y2) / 2;
        dfs(x1, y1, x2, mid, !flag), dfs(x1, mid, x2, y2, !flag);
        for (int i = x1; i < x2; i++) {
            up[0] = down[0] = mid;
            for (int t = 1; t <= k + 1; t++)
                up[t] = y1, down[t] = y2;
            for (int j = i + 1; j <= x2; j++) {
                for (int t = 1; t <= k + 1; t++) {
                    while (calc(i, up[t], j, mid) >= t) up[t]++;
                    while (calc(i, mid, j, down[t]) >= t) down[t]--;
                }
                for (int t = 0; t <= k; t++)
                    ans += (up[t] - up[t + 1]) * (down[k - t + 1] - down[k - t]);
            }
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%s", c[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (c[i][j] - '0');
    dfs(0, 0, n, m, 0);
    printf("%lld\n", ans);
    return 0;
}