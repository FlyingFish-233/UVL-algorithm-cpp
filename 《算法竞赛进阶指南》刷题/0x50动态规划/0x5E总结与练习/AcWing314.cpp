# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10;

int n;
int a[NR];
int f[NR], cnt[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    a[0] = 2e9, a[n + 1] = -2e9, f[0] = 0, cnt[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) if (a[j] > a[i]) {
            if (f[i] < f[j] + 1) f[i] = f[j] + 1, cnt[i] = cnt[j];
            else if (f[i] == f[j] + 1) cnt[i] += cnt[j];
        }
        for (int j = 0; j < i; j++)
            if (a[j] == a[i]) cnt[j] = 0;
    }
    printf("%d %d\n", f[n + 1] - 1, cnt[n + 1]);
    return 0;
}