# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int A, B, C, D;
double f[14][14][14][14][5][5];

double dfs(int a, int b, int c, int d, int x, int y)
{
    if (a + (x == 1) + (y == 1) >= A && b + (x == 2) + (y == 2) >= B
        && c + (x == 3) + (y == 3) >= C && d + (x == 4) + (y == 4) >= D) return 0;
    if (f[a][b][c][d][x][y] > 0) return f[a][b][c][d][x][y];
    int cnt = a + b + c + d + (x != 0) + (y != 0);
    double ans = 1;
    if (a < 13) ans += dfs(a + 1, b, c, d, x, y) * (13 - a) / (54 - cnt);
    if (b < 13) ans += dfs(a, b + 1, c, d, x, y) * (13 - b) / (54 - cnt);
    if (c < 13) ans += dfs(a, b, c + 1, d, x, y) * (13 - c) / (54 - cnt);
    if (d < 13) ans += dfs(a, b, c, d + 1, x, y) * (13 - d) / (54 - cnt);
    if (x == 0) {
        double f_min = 2e9;
        for (int i = 1; i <= 4; i++)
            f_min = min(f_min, dfs(a, b, c, d, i, y) / (54 - cnt));
        ans += f_min;
    }
    if (y == 0) {
        double f_min = 2e9;
        for (int i = 1; i <= 4; i++)
            f_min = min(f_min, dfs(a, b, c, d, x, i) / (54 - cnt));
        ans += f_min;
    }
    return f[a][b][c][d][x][y] = ans;
}

int main()
{
    scanf("%d%d%d%d", &A, &B, &C, &D);
    if (max(A - 13, 0) + max(B - 13, 0) + max(C - 13, 0) + max(D - 13, 0) > 2)
        return printf("-1.000\n"), 0;
    printf("%.3f\n", dfs(0, 0, 0, 0, 0, 0));
    return 0;
}