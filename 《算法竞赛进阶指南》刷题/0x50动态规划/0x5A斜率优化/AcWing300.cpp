# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e3 + 10;

int n, s;
long long sumt[NR], sumc[NR];
long long f[NR];

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1, t, c; i <= n; i++) {
        scanf("%d%d", &t, &c);
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            f[i] = min(f[i], f[j] + sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]));
    printf("%lld\n", f[n]);
    return 0;
}