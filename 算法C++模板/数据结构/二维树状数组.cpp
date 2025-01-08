// LOJ133 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = (1 << 12) + 10;

int n, m;
long long s[NR][NR];

int lowbit(int x)
{
    return x & (-x);
}

void modify(int x, int y, int delta)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            s[i][j] += delta;
}

long long getsum(int x, int y)
{
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ans += s[i][j];
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    int op, x, y, z, w;
    while (scanf("%d", &op) != EOF) {
        scanf("%d%d%d", &x, &y, &z);
        if (op == 1) modify(x, y, z);
        if (op == 2) {
            scanf("%d", &w);
            printf("%lld\n", getsum(z, w) - getsum(x - 1, w) - getsum(z, y - 1) + getsum(x - 1, y - 1));
        }
    }
    return 0;
}