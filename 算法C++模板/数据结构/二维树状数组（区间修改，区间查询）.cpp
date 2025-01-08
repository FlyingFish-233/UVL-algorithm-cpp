// LOJ135 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = (1 << 11) + 10;

int n, m;
long long s[4][NR][NR];

int lowbit(int x)
{
    return x & (-x);
}

void modify(int t, int x, int y, int delta)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            s[t][i][j] += delta;
}

long long getsum(int t, int x, int y)
{
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ans += s[t][i][j];
    return ans;
}

void change(int x, int y, int delta)
{
    modify(0, x, y, delta);
    modify(1, x, y, x * delta);
    modify(2, x, y, y * delta);
    modify(3, x, y, x * y * delta);
}

long long calc(int x, int y)
{
    return (x + 1) * (y + 1) * getsum(0, x, y) - (y + 1) * getsum(1, x, y)
            - (x + 1) * getsum(2, x, y) + getsum(3, x, y);
}

// s[1~x][1~y] = Sum(d[i][j]*(x+1-i)*(y+1-i))
// = (x+1)*(y+1)*Sum(d[i][j]) - (y+1)*Sum(i*d[i][j]) - (x+1)*Sum(j*d[i][j]) + Sum(i*j*d[i][j])
int main()
{
    scanf("%d%d", &n, &m);
    int op, x, y, z, w, k;
    while (scanf("%d", &op) != EOF) {
        scanf("%d%d%d%d", &x, &y, &z, &w);
        if (op == 1) {
            scanf("%d", &k);
            change(x, y, k);
            change(x, w + 1, -k);
            change(z + 1, y, -k);
            change(z + 1, w + 1, k);
        }
        if (op == 2) printf("%lld\n", calc(z, w) - calc(x - 1, w) - calc(z, y - 1) + calc(x - 1, y - 1));
    }
    return 0;
}