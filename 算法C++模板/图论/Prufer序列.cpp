# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e6 + 10;

int n, m;
int f[NR], p[NR], d[NR];
// f[i]为父亲序列, p[i]为prufer序列, d[i]为节点i的度数减1

void father_to_prufer()
{
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &f[i]), d[f[i]]++;
    for (int i = 1, j = 1; i <= n - 2; i++, j++) {
        while (d[j] > 0) j++;
        p[i] = f[j];
        while (i <= n - 2 && --d[p[i]] == 0 && p[i] < j) p[i + 1] = f[p[i]], i++;
    }
    long long ans = 0;
    for (int i = 1; i <= n - 2; i++)
        ans ^= 1ll * i * p[i];
    printf("%lld\n", ans);
}

void prufer_to_father()
{
    for (int i = 1; i <= n - 2; i++)
        scanf("%d", &p[i]), d[p[i]]++;
    p[n - 1] = n, d[n]++;
    for (int i = 1, j = 1; i <= n - 1; i++, j++) {
        while (d[j] > 0) j++;
        f[j] = p[i];
        while (i <= n - 1 && --d[p[i]] == 0 && p[i] < j) f[p[i]] = p[i + 1], i++;
    }
    long long ans = 0;
    for (int i = 1; i <= n - 1; i++)
        ans ^= 1ll * i * f[i];
    printf("%lld\n", ans);
}

int main()
{
    scanf("%d%d", &n, &m);
    if (m == 1) father_to_prufer();
    if (m == 2) prufer_to_father();
    return 0;
}