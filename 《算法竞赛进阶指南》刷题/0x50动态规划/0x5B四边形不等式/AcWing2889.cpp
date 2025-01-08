# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10;

int n;
int s[NR];
int f[NR][NR], p[NR][NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]), s[i] += s[i - 1];
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0, p[i][i] = i;
    for (int i = n; i >= 1; i--)
        for (int j = i + 1; j <= n; j++)
            for (int k = p[i][j - 1]; k <= p[i + 1][j]; k++) if (k >= i && k < j) {
                int val = f[i][k] + f[k + 1][j] + s[j] - s[i - 1];
                if (f[i][j] > val) f[i][j] = val, p[i][j] = k;
            }
    printf("%d\n", f[1][n]);
    return 0;
}