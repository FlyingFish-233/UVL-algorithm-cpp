// P7962 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10, MR = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
int a[NR], d[NR], sd[NR];
int f[2][MR];

/*
1. 方差 = n * Sum(a[i]^2) - Sum(a[i])^2 = Sum((a[i] - a[j])^2)
2. 操作<=>交换差分序列中d[i-1]与d[i]
3. 感觉:差分序列先减后增时, 方差最小
 => 考虑控制Sum(a[i])做DP

f[i][s]表示d[1]~d[i]确定,且s=a[1]+...+a[i+1]时Sum(a[i]^2)的最小值
1. d[i]置前: f[i][s+i*d[i]] = f[i-1][s] + 2*s*d[i] + i*d[i]^2
2. d[i]置后: f[i][s+(d[1]+...+d[i])] = f[i-1][s] + (d[1]+...+d[i])^2
初值: f[0][0] = 0, 其余为INF
答案: min(n*f[n][s] - s^2)

细节:
1. 滚动数组优化空间
2. 最后几组数据中很多d[i]=0, 而d[i]=0在转移时可直接跳过
*/
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), d[i - 1] = a[i] - a[i - 1];
    sort(d + 1, d + (n - 1) + 1);
    for (int i = 1; i <= n - 1; i++)
        sd[i] = sd[i - 1] + d[i];

    int lim = sd[n - 1] * n;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n - 1; i++) if (d[i] != 0) {
        for (int s = 0; s <= lim; s++) if (f[0][s] != INF) {
            f[1][s + i * d[i]] = min(f[1][s + i * d[i]], f[0][s] + 2 * s * d[i] + i * d[i] * d[i]);
            f[1][s + sd[i]] = min(f[1][s + sd[i]], f[0][s] + sd[i] * sd[i]);
        }
        memcpy(f[0], f[1], sizeof(f[1]));
        memset(f[1], 0x3f, sizeof(f[1]));
    }
    long long ans = 1e17;
    for (int s = 0; s <= lim; s++) if (f[0][s] != INF)
        ans = min(ans, 1ll * n * f[0][s] - 1ll * s * s);
    printf("%lld\n", ans);
    return 0;
}