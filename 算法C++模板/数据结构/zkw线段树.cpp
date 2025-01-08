// P3372 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
long long a[NR];

int N;
long long sum[NR << 2], tag[NR << 2];

void build()
{
    for (N = 1; N <= n + 1; N <<= 1); // 0~n需要n+1个叶子节点
    for (int i = 1; i <= n; i++)
        sum[N + i] = a[i]; // 编号为N+i的节点,是第i+1个叶子节点,对应a[i]
    for (int i = N - 1; i >= 1; i--)
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void modify(int s, int t, long long k)
{
    int lNum = 0, rNum = 0, nNum = 1;
    for (s = N + s - 1, t = N + t + 1; s ^ t ^ 1; s >>= 1, t >>= 1, nNum <<= 1) {
        sum[s] += k * lNum, sum[t] += k * rNum;
        if (~s & 1) tag[s ^ 1] += k, sum[s ^ 1] += k * nNum, lNum += nNum;
        if (t & 1) tag[t ^ 1] += k, sum[t ^ 1] += k * nNum, rNum += nNum;
    }
    for ( ; s; s >>= 1, t >>= 1)
        sum[s] += k * lNum, sum[t] += k * rNum;
}

long long getsum(int s, int t)
{
    int lNum = 0, rNum = 0, nNum = 1;
    long long ans = 0;
    for (s = N + s - 1, t = N + t + 1; s ^ t ^ 1; s >>= 1, t >>= 1, nNum <<= 1) {
        ans += tag[s] * lNum, ans += tag[t] * rNum;
        if (~s & 1) ans += sum[s ^ 1], lNum += nNum;
        if (t & 1) ans += sum[t ^ 1], rNum += nNum;
    }
    for ( ; s; s >>= 1, t >>= 1)
        ans += tag[s] * lNum, ans += tag[t] * rNum;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build();
    while (m--) {
        int op, x, y; long long k;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) scanf("%lld", &k), modify(x, y, k);
        if (op == 2) printf("%lld\n", getsum(x, y));
    }
    return 0;
}