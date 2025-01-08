// AcWing2 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 1e3 + 10;

int n, m;
int w[NR], v[NR];
int f[MR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &w[i], &v[i]);
    memset(f, -0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--)
            f[j] = max(f[j], f[j - w[i]] + v[i]);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}