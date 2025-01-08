# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e7 + 10, PR = 998244353;

int inv[NR], s[NR];
bool flag[NR];
int num[NR], p_max[NR];
int f[NR], sum[NR];

int main()
{
    inv[1] = 1;
    for (int i = 2; i <= 1e7; i++)
        inv[i] = 1ll * (PR - PR / i) * inv[PR % i] % PR;
    for (int i = 1; i <= 1e7; i++)
        s[i] = (s[i - 1] + inv[i]) % PR;

    for (int i = 2; i <= 1e7; i++) if (!flag[i])
        for (int j = 2; i * j <= 1e7; j++)
            flag[i * j] = true, p_max[i * j] = i;
    num[1] = 1;
    for (int i = 2; i <= 1e7; i++) {
        if (!flag[i]) { num[i] = 2; continue; }
        int x = i, cnt = 0;
        while (x % p_max[i] == 0) x /= p_max[i], cnt++;
        num[i] = num[x] * (cnt + 1);
    }

    for (int i = 2; i <= 1e7; i++)
        f[i] = (f[i - 1] + s[i - 1] - num[i] + 1) % PR;
    for (int i = 1; i <= 1e7; i++)
        sum[i] = (sum[i - 1] + f[i]) % PR;

    int T;
    scanf("%d", &T);
    while (T--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", (sum[r] - sum[l - 1] + PR) % PR);
    }
    return 0;
}

