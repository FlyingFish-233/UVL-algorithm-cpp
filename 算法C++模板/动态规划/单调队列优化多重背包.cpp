// AcWing6 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 2e4 + 10;

int n, m;
int w[NR], v[NR], c[NR];
int f[MR], q[MR];
// f[i][j + k * w[i]] = max(f[i - 1][j + t * w[i]] + (k - t) * v[i]) (k - c[i] <= t <= k - 1)

int calc(int i, int j, int k)
{
    return f[j + k * w[i]] - k * v[i];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &w[i], &v[i], &c[i]);
    memset(f, -0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < w[i]; j++) {
            int lim = (m - j) / w[i], l = 1, r = 0;
            for (int k = lim - 1; k >= max(lim - c[i], 0); k--) {
                while (l <= r && calc(i, j, q[r]) <= calc(i, j, k)) r--;
                q[++r] = k;
            }
            for (int k = lim; k >= 0; k--) {
                while (l <= r && q[l] > k - 1) l++;
                if (l <= r) f[j + k * w[i]] = max(f[j + k * w[i]], calc(i, j, q[l]) + k * v[i]);
                if (k - c[i] - 1 >= 0) {
                    while (l <= r && calc(i, j, q[r]) <= calc(i, j, k - c[i] - 1)) r--;
                    q[++r] = k - c[i] - 1;
                }
            }
        }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}