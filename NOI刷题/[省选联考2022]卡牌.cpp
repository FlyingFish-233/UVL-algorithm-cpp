// P8292 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2010, MR = (1 << 13) - 1;
const int mod = 998244353;

int n, m;
int a[NR];
int v[NR], p[NR], _p[NR]; // p[i]为第i个质数, _p[i]为质数i的排名
int pp[NR], p_max[NR]; // pp[i]为i的质因数分解(仅包含前13个质数的状压), p_max[i]为i的最大质因数
int f[MR + 10][NR], cnt1[MR + 10]; // f[sta][i]为不被p[t](t属于sta)整除, 且被p[i]整除的数的个数
int c, cp[20010];

// 一个数(<=2000)至多只能被一个(>=43)的质数整除
// "所有数均不被p[t](t属于sta)整除, 且存在被p[i](i>13)整除的数"的方案数
// = 求积(2^f[sta][i]-1) * 2^left [left=f[sta][0]-Sum(f[sta][i]), 其中i>13&p[i]属于询问集合]
// 容斥 => "对任意p[i]属于询问集合, 均存在被p[i]整除的数"的方案数

int qpow(int x, int y)
{
    int ans = 1;
    for (int i = y; i; i >>= 1, x = 1ll * x * x % mod)
        if (i & 1) ans = 1ll * ans * x % mod;
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), a[x]++;
    for (int i = 2; i <= 2000; i++) {
        if (v[i] == 0) p[++p[0]] = i, _p[i] = p[0];
        for (int j = 1; j <= p[0] && p[j] <= i && i * p[j] <= 2000; j++)
            v[i * p[j]] = p[j];
        for (int j = 1; j <= p[0]; j++) if (i % p[j] == 0) {
            if (j <= 13) pp[i] |= 1 << (j - 1);
            p_max[i] = j;
        }
    }
    for (int sta = 0; sta <= MR; sta++) {
        for (int i = 2; i <= 2000; i++) if (!(sta & pp[i])) {
            if (p_max[i] > 13) f[sta][p_max[i]] += a[i];
            f[sta][0] += a[i];
        }
        f[sta][0] += a[1];
        for (int i = 0; i < 13; i++)
            cnt1[sta] += sta >> i & 1;
    }
    scanf("%d", &m);
    while (m--) {
        int c, lim = 0;
        scanf("%d", &c);
        for (int i = 1; i <= c; i++) {
            scanf("%d", &cp[i]), cp[i] = _p[cp[i]];
            if (cp[i] <= 13) lim |= 1 << (cp[i] - 1);
        }
        int ans = 0;
        for (int sta = 0; sta <= MR; sta++) if ((sta | lim) == lim) {
            int now = 1, left = f[sta][0];
            for (int i = 1; i <= c; i++) if (cp[i] > 13)
                now = 1ll * now * (qpow(2, f[sta][cp[i]]) - 1) % mod, left -= f[sta][cp[i]];
            now = 1ll * now * qpow(2, left) % mod;
            if (cnt1[sta] & 1) ans = (ans - now) % mod;
            else ans = (ans + now) % mod;
        }
        printf("%d\n", (ans % mod + mod) % mod);
    }
    return 0;
}

