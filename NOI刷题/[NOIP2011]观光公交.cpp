// P1315 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

int n, m, k;
int d[NR], t[NR], a[NR], b[NR];
int t_max[NR], ari[NR], p[NR], s[NR];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &t[i], &a[i], &b[i]);
        t_max[a[i]] = max(t_max[a[i]], t[i]), s[b[i]]++;
    }
    for (int i = 1; i <= n; i++)
        s[i] += s[i - 1];
    while (k--) {
        for (int i = 1; i <= n; i++)
            ari[i] = max(ari[i - 1], t_max[i - 1]) + d[i - 1];
        p[n] = n;
        for (int i = n - 1; i >= 1; i--)
            if (ari[i] > t_max[i]) p[i] = p[i + 1];
            else p[i] = i;
        int tmp = 0;
        for (int i = 1; i <= n - 1; i++)
            if (d[i] > 0 && (tmp == 0 || s[p[i + 1]] - s[i] > s[p[tmp + 1]] - s[tmp]))
                tmp = i;
        if (tmp == 0) break;
        d[tmp]--;
    }
    for (int i = 1; i <= n; i++)
        ari[i] = max(ari[i - 1], t_max[i - 1]) + d[i - 1];
    long long ans = 0;
    for (int i = 1; i <= m; i++)
        ans += ari[b[i]] - t[i];
    printf("%lld\n", ans);
    return 0;
}