// LOJ134 (100 pts)
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

// d[x][y] = a[x][y] - a[x-1][y] - a[x][y-1] + a[x-1][y-1]
int main()
{
    scanf("%d%d", &n, &m);
    int op, x, y, z, w, k;
    while (scanf("%d", &op) != EOF) {
        scanf("%d%d", &x, &y);
        if (op == 1) {
            scanf("%d%d%d", &z, &w, &k);
            modify(x, y, k);
            modify(x, w + 1, -k);
            modify(z + 1, y, -k);
            modify(z + 1, w + 1, k);
        }
        if (op == 2) printf("%lld\n", getsum(x, y));
    }
    return 0;
}