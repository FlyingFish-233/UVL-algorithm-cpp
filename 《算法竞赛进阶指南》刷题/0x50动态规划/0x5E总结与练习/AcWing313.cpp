# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n, m;
int v[NR][NR];
int f[NR][NR], pre[NR][NR];

void print(int i, int j)
{
    if (i == 0 && j == 0) return;
    print(pre[i][j], j - 1);
    printf("%d ", i);
}

int main()
{
    scanf("%d%d", &m, &n);
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            scanf("%d", &v[i][j]);
    memset(f, -0x3f, sizeof(f)), f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) if (f[i][j] < f[k][j - 1])
                f[i][j] = f[k][j - 1], pre[i][j] = k;
            f[i][j] += v[i][j];
        }
    int ans = -2e9, last = 0;
    for (int i = 1; i <= n; i++)
        if (ans < f[i][m]) ans = f[i][m], last = i;
    printf("%d\n", ans);
    print(last, m), puts("");
    return 0;
}