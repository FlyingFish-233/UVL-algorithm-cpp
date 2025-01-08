# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e5 + 10;

int n, s;
long long sumt[NR], sumc[NR];
long long f[NR];
int q[NR];

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1, t, c; i <= n; i++) {
        scanf("%d%d", &t, &c);
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    memset(f, 0x3f, sizeof(f)), f[0] = 0;
    int l = 1, r = 0;
    q[++r] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && f[q[l + 1]] - f[q[l]] <= (s + sumt[i]) * (sumc[q[l + 1]] - sumc[q[l]])) l++;
        f[i] = f[q[l]] - (s + sumt[i]) * sumc[q[l]] + sumt[i] * sumc[i] + s * sumc[n];
        while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]])
            >= (sumc[q[r]] - sumc[q[r - 1]]) * (f[i] - f[q[r]])) r--;
        q[++r] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}