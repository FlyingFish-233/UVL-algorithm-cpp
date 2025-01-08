// AcWing11 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 1e3 + 10;
const int mod = 1e9 + 7;

int n, m;
int w[NR], v[NR];
int f[MR], cnt[MR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &w[i], &v[i]);
    memset(f, -0x3f, sizeof(f)), f[0] = 0, cnt[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--) {
            if (f[j] < f[j - w[i]] + v[i])
                f[j] = f[j - w[i]] + v[i], cnt[j] = cnt[j - w[i]];
            else if (f[j] == f[j - w[i]] + v[i])
                (cnt[j] += cnt[j - w[i]]) %= mod;
        }
    int ans = 0, tot = 0;
    for (int i = 1; i <= m; i++)
        if (ans < f[i]) ans = f[i], tot = cnt[i];
        else if (ans == f[i]) (tot += cnt[i]) %= mod;
    printf("%d\n", tot);
    return 0;
}