# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <map>

using namespace std;

int fastPow(int a, int b, int p)
{
    int ans = 1;
    for (int i = b; i; i >>= 1, a = 1ll * a * a % p)
        if (i & 1) ans = 1ll * ans * a % p;
    return ans;
}

int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}

int solve(int a, int b, int p)
{
    int x, y, d = gcd(a, p), t = abs(p / d);
    if (b % d != 0) return -1;
    exgcd(a, p, x, y), x = 1ll * x * (b / d) % t;
    return (x % t + t) % t;
}

map<int, int> ha;

// (a^t)^i = b * (a^j)
int bsgs(int a, int b, int p)
{
    int t = (int)sqrt(p) + 1;
    b %= p, ha.clear();
    for (int j = 0, val = b; j < t; j++, val = 1ll * val * a % p)
        ha[val] = j;
    a = fastPow(a, t, p);
    if (a == 0) return (b == 0) ? 1 : -1;
    for (int i = 0, val = 1; i <= t; i++, val = 1ll * val * a % p) {
        int j = (ha.count(val) == 0) ? -1 : ha[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}

int main()
{
    int T, K;
    scanf("%d%d", &T, &K);
    while (T--) {
        int a, b, p;
        scanf("%d%d%d", &a, &b, &p);
        int ans = 0;
        if (K == 1) ans = fastPow(a, b, p);
        if (K == 2) ans = solve(a, b, p);
        if (K == 3) ans = bsgs(a, b, p);
        if (ans == -1) printf("Orz, I cannot find x!\n");
        else printf("%d\n", ans);
    }
    return 0;
}