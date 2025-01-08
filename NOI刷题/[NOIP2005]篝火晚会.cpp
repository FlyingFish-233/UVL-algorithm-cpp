// P1053 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

int n;
int l[NR], r[NR];
int tot, a[NR];
int cnt1[NR], cnt2[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &l[i], &r[i]);
    for (int i = 1; i <= n; i++)
        if ((l[l[i]] != i && r[l[i]] != i) || (l[r[i]] != i && r[r[i]] != i))
            return printf("-1\n"), 0;
    a[++tot] = 1, a[++tot] = r[a[1]];
    while (a[tot] != 1) {
        if (l[a[tot]] == a[tot - 1]) a[tot + 1] = r[a[tot]];
        else a[tot + 1] = l[a[tot]];
        tot++;
    }
    if (tot <= n) return printf("-1\n"), 0;
    for (int i = 1; i <= n; i++)
        cnt1[(a[i] - i + n) % n]++, cnt2[(a[i] + i) % n]++;
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, max(cnt1[i], cnt2[i]));
    printf("%d\n", n - ans);
    return 0;
}