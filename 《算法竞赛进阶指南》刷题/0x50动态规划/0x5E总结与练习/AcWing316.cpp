# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1e4 + 10;

int n, t;
int a[NR];
int f[NR][MR << 1];
int cnt;

void print(int i, int j)
{
    if (i == 1) return;
    if (f[i][j] == -1) print(i - 1, j + a[i]);
    if (f[i][j] == 1) print(i - 1, j - a[i]), printf("%d\n", i - (cnt++) - 1);
}

int main()
{
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    f[1][a[1] + 10000] = 1;
    f[2][a[1] - a[2] + 10000] = -1;
    for (int i = 3; i <= n; i++)
        for (int j = 0; j <= 2e4; j++) if (f[i - 1][j]) {
            if (j - a[i] >= 0 && j - a[i] <= 2e4) f[i][j - a[i]] = -1;
            if (j + a[i] >= 0 && j + a[i] <= 2e4) f[i][j + a[i]] = 1;
        }
    print(n, t + 1e4);
    for (int i = 1; i <= n - 1 - cnt; i++) puts("1");
    return 0;
}