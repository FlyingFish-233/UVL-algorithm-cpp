// P5091 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e7 + 10;

int phi(int x)
{
    int ans = x;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) {
            ans -= ans / i;
            while (x % i == 0) x /= i;
        }
    if (x > 1) ans -= ans / x;
    return ans;
}

int qpow(int a, int b, int p)
{
    int ans = 1;
    for (int i = b; i; i >>= 1, a = 1ll * a * a % p)
        if (i & 1) ans = 1ll * ans * a % p;
    return ans % p;
}

int main()
{
    int a, mod;
    scanf("%d%d", &a, &mod);
    int ph = phi(mod), b = 0;
    char c = getchar(); bool flag = false;
    for ( ; c < '0' || c > '9'; c = getchar());
    for ( ; c >= '0' && c <= '9'; c = getchar()) {
        b = b * 10 + c - 48;
        if (b >= ph) b %= ph, flag = true;
    }
    if (flag) b += ph;
    printf("%d\n", qpow(a, b, mod));
    return 0;
}