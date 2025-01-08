# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n;
int a[10][10], s[10][10];
double avg, f[15][10][10][10][10];

double dfs(int k, int x1, int y1, int x2, int y2)
{
    if (k == 0) {
        double save = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] - avg;
        return save * save;
    }
    if (f[k][x1][y1][x2][y2] >= 0) return f[k][x1][y1][x2][y2];
    double ans = 2e9;
    for (int i = x1; i < x2; i++) {
        ans = min(ans, dfs(0, x1, y1, i, y2) + dfs(k - 1, i + 1, y1, x2, y2));
        ans = min(ans, dfs(k - 1, x1, y1, i, y2) + dfs(0, i + 1, y1, x2, y2));
    }
    for (int i = y1; i < y2; i++) {
        ans = min(ans, dfs(0, x1, y1, x2, i) + dfs(k - 1, x1, i + 1, x2, y2));
        ans = min(ans, dfs(k - 1, x1, y1, x2, i) + dfs(0, x1, i + 1, x2, y2));
    }
    return f[k][x1][y1][x2][y2] = ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            scanf("%d", &a[i][j]), s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
    avg = 1.0 * s[8][8] / n;
    memset(f, -1, sizeof(f));
    printf("%.3f\n", sqrt(dfs(n - 1, 1, 1, 8, 8) / n));
    return 0;
}