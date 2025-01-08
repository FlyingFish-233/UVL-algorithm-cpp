# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e7 + 10;

int n;

int phi(int x)
{
    int ans = x;
    for (int i = 2; 1ll * i * i <= x; i++)
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            ans = 1ll * ans * (i - 1) / i;
        }
    if (x > 1) ans = 1ll * ans * (x - 1) / x;
    return ans;
}

int main()
{
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; 1ll * i * i <= n; i++) {
        if (n % i != 0) continue;
        ans += i * phi(n / i);
        if (i * i != n) ans += (n / i) * phi(i);
    }
    printf("%lld\n", ans);
    return 0;
}