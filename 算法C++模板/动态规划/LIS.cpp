// AcWing895 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;

int n;
int a[NR];
int f[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int ans = 0; f[0] = -2e9;
    for (int i = 1; i <= n; i++){
        int k = lower_bound(f, f + ans + 1, a[i]) - f;
        f[k] = a[i], ans = max(ans, k);
    }
    printf("%d\n", ans);
    return 0;
}