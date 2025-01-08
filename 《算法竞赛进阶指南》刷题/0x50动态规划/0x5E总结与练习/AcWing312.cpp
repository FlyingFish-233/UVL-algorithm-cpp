# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n, m;
int a[400], cnt[5];
int f[50][50][50][50];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1, x; i <= m; i++)
        scanf("%d", &x), cnt[x]++;
    f[0][0][0][0] = a[1];
    for (int x = 0; x <= cnt[1]; x++)
    for (int y = 0; y <= cnt[2]; y++)
    for (int z = 0; z <= cnt[3]; z++)
    for (int w = 0; w <= cnt[4]; w++) {
        int now = x + 2 * y + 3 * z + 4 * w + 1;
        f[x + 1][y][z][w] = max(f[x + 1][y][z][w], f[x][y][z][w] + a[now + 1]);
        f[x][y + 1][z][w] = max(f[x][y + 1][z][w], f[x][y][z][w] + a[now + 2]);
        f[x][y][z + 1][w] = max(f[x][y][z + 1][w], f[x][y][z][w] + a[now + 3]);
        f[x][y][z][w + 1] = max(f[x][y][z][w + 1], f[x][y][z][w] + a[now + 4]);
    }
    printf("%d\n", f[cnt[1]][cnt[2]][cnt[3]][cnt[4]]);
    return 0;
}