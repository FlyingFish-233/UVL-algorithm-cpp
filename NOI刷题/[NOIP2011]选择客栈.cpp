// P1311 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

int n, k, p;
int a[NR], b[NR];
int cnt[51];

int main()
{
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i], &b[i]);
    long long ans = 0;
    for (int i = 1, pre = 0; i <= n; i++) {
        if (b[i] <= p) {
            for (int j = pre + 1; j < i; j++) cnt[a[j]]++;
            ans += cnt[a[i]];
            cnt[a[i]]++, pre = i;
        }
        else ans += cnt[a[i]];
    }
    printf("%lld\n", ans);
    return 0;
}