// P7515 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 310;

int n, m;
int a[NR][NR], b[NR][NR];
int g[NR << 1][NR << 1];
long long dis[NR << 1];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n - 1; i++)
            for (int j = 1; j <= m - 1; j++)
                scanf("%d", &b[i][j]);
        for (int i = 2; i <= n; i++)
            for (int j = 2; j <= m; j++)
                a[i][j] = b[i - 1][j - 1] - a[i - 1][j] - a[i][j - 1] - a[i - 1][j - 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if ((i + j) & 1) g[i][j + n] = 1e6 - a[i][j], g[j + n][i] = a[i][j];
                else g[i][j + n] = a[i][j], g[j + n][i] = 1e6 - a[i][j];
            }
        memset(dis, 0x3f, sizeof(dis)), dis[0] = 0;
        bool flag;
        for (int k = 1; k <= n + m + 1; k++) {
            flag = false;
            for (int i = 0; i <= n + m; i++) {
                int l = (i <= n) ? n + 1 : 1, r = (i <= n) ? n + m : n;
                if (i == 0) l = 1, r = n + m;
                for (int j = l; j <= r; j++)
                    if (dis[j] > dis[i] + g[i][j]) dis[j] = dis[i] + g[i][j], flag = true;
            }
            if (!flag) break;
        }
        if (flag) { printf("NO\n"); continue; }
        printf("YES\n");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if ((i + j) & 1) printf("%lld ", a[i][j] + dis[j + n] - dis[i]);
                else printf("%lld ", a[i][j] + dis[i] - dis[j + n]);
            }
            puts("");
        }
    }
    return 0;
}

