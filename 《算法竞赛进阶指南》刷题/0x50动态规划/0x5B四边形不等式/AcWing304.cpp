# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Node
{
    int j, l, r;
};

int n, l, p;
char str[NR][31];
int s[NR];

long double f[NR];
int pre[NR], nxt[NR];
Node q[NR];

long double val(int j, int i)
{
    long double sum = 1, a = abs(s[i] - s[j] + i - j - 1 - l);
    for (int i = p; i; i >>= 1, a *= a)
        if (i & 1) sum *= a;
    return f[j] + sum;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &l, &p);
        for (int i = 1; i <= n; i++)
            scanf("%s", str[i]), s[i] = s[i - 1] + strlen(str[i]);
        int h = 1, t = 0;
        q[++t] = (Node) {0, 1, n};
        for (int i = 1; i <= n; i++) {
            while (h <= t && q[h].r <= i - 1) h++;
            q[h].l = i, pre[i] = q[h].j, f[i] = val(q[h].j, i);
            if (val(i, n) >= val(q[t].j, n)) continue;
            while (h <= t && val(i, q[t].l) <= val(q[t].j, q[t].l)) t--;
            int L = q[t].l, R = q[t].r, pos = q[t].r + 1;
            while (L <= R) {
                int mid = (L + R) >> 1;
                if (val(i, mid) <= val(q[t].j, mid)) R = mid - 1, pos = mid;
                else L = mid + 1;
            }
            q[t].r = pos - 1, q[++t] = (Node) {i, pos, n};
        }
        if (f[n] > 1e18) printf("Too hard to arrange\n");
        else {
            printf("%lld\n", (long long) f[n]);
            for (int i = n; i >= 1; i = pre[i])
                nxt[pre[i]] = i;
            for (int i = 0; i < n; i = nxt[i]) {
                printf("%s", str[i + 1]);
                for (int j = i + 2; j <= nxt[i]; j++)
                    printf(" %s", str[j]);
                puts("");
            }
        }
        printf("--------------------\n");
    }
    return 0;
}