// P7113 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef __int128 LL;

const int NR = 1e5 + 10, MR = 5e5 + 10;

void print(LL x)
{
    if (x >= 10) print(x / 10);
    putchar(x % 10 + '0');
}

LL gcd(LL x, LL y)
{
    if (x == 0 || y == 0) return x + y;
    return gcd(y, x % y);
}

struct Number
{
    LL p, q;
    Number() { p = 0, q = 1; }
    Number(LL p0, LL q0) { p = p0 / gcd(p0, q0), q = q0 / gcd(p0, q0); }
    Number operator + (const Number &A) const {
        LL lcm = q / gcd(q, A.q) * A.q;
        return Number(lcm / q * p + lcm / A.q * A.p, lcm);
    }
    Number operator / (const int &x) const {
        return Number(p, q * x);
    }
};

struct Edge
{
    int to, next;
};

int n, m;
int gsz, fte[NR], deg[NR], in[NR];
Edge g[MR];
int q[NR]; Number f[NR];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &deg[i]);
        for (int j = 1, x; j <= deg[i]; j++)
            scanf("%d", &x), addEdge(i, x), in[x]++;
    }
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
        q[++r] = i, f[i] = Number(1, 1);
    while (l <= r) {
        int x = q[l++];
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            f[y] = f[y] + f[x] / deg[x];
            if (--in[y] == 0) q[++r] = y;
        }
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0) {
            print(f[i].p);
            putchar(' ');
            print(f[i].q);
            putchar('\n');
        }
    return 0;
}
