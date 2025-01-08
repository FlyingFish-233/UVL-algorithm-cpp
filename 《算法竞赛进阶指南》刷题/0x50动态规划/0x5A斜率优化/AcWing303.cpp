# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m, p;
long long d[NR], a[NR], s[NR];
long long f[110][NR];
int q[NR];

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 2; i <= n; i++)
        scanf("%lld", &d[i]), d[i] += d[i - 1];
    for (int i = 1, h, t; i <= m; i++)
        scanf("%d%d", &h, &t), a[i] = t - d[h];
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++)
        s[i] = s[i - 1] + a[i];
    memset(f[0], 0x3f, sizeof(f[0])), f[0][0] = 0;
    for (int i = 1; i <= p; i++) {
        int l = 1, r = 0;
        q[++r] = 0;
        for (int j = 1; j <= m; j++) {
            while (l < r && f[i - 1][q[l + 1]] + s[q[l + 1]] - f[i - 1][q[l]] - s[q[l]]
                <= a[j] * (q[l + 1] - q[l])) l++;
            f[i][j] = f[i - 1][q[l]] + a[j] * (j - q[l]) - (s[j] - s[q[l]]);
            while (l < r && (f[i - 1][q[r]] + s[q[r]] - f[i - 1][q[r - 1]] - s[q[r - 1]]) * (j - q[r])
                >= (q[r] - q[r - 1]) * (f[i - 1][j] + s[j] - f[i - 1][q[r]] - s[q[r]])) r--;
            q[++r] = j;
        }
    }
    printf("%lld\n", f[p][m]);
    return 0;
}