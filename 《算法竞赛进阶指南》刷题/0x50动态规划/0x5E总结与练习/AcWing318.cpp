# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 200, MR = 2e4 + 10;

int n, m;
int a[10], w[NR];
bool f[MR];

int main()
{
    while (true) {
        n = m = 0;
        for (int i = 1; i <= 6; i++)
            scanf("%d", &a[i]), m += i * a[i];
        if (m == 0) break;
        if (m & 1) { printf("Can't\n"); continue; }
        m /= 2;
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= a[i]; a[i] -= j, j *= 2)
                w[++n] = i * j;
            if (a[i] > 0) w[++n] = i * a[i];
        }
        memset(f, false, sizeof(f)), f[0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= w[i]; j--)
                f[j] |= f[j - w[i]];
        if (f[m]) printf("Can\n");
        else printf("Can't\n");
    }
    return 0;
}