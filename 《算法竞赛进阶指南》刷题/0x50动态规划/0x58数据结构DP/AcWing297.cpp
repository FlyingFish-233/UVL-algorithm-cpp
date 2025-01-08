# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const int mod = 1e9 + 7;

int n, m, len;
int a[NR], b[NR];
int f[NR][NR], s[NR];

int lowbit(int x)
{
    return x & (-x);
}

void modify(int x, int delta)
{
    for (int i = x; i <= n + 1; i += lowbit(i))
        (s[i] += delta) %= mod;
}

int getsum(int x)
{
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        (sum += s[i]) %= mod;
    return sum;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; c++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        memcpy(b, a, sizeof(a));
        sort(b + 1, b + n + 1);
        len = unique(b + 1, b + n + 1) - b - 1;
        for (int i = 1; i <= n; i++)
            a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b + 1;
        memset(f, 0, sizeof(f)), f[0][0] = a[0] = 1;
        for (int i = 1; i <= m; i++) {
            memset(s, 0, sizeof(s));
            modify(a[0], f[i - 1][0]);
            for (int j = 1; j <= n; j++)
                f[i][j] = getsum(a[j] - 1), modify(a[j], f[i - 1][j]);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            (ans += f[m][i]) %= mod;
        printf("Case #%d: %d\n", c, ans);
    }
    return 0;
}