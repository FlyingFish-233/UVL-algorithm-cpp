// P8819 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 5e5 + 10;

int n, m;
LL sum, a[NR], A[NR];
LL now, A0[NR];

int main()
{
    srand(1000001);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        a[i] = rand(), sum += a[i];
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), A[y] += a[x], now += a[x];
    memcpy(A0, A, sizeof(A));
    int T;
    scanf("%d", &T);
    while (T--) {
        int op, x, y;
        scanf("%d%d", &op, &x);
        if (op == 1) scanf("%d", &y), A0[y] -= a[x], now -= a[x];
        if (op == 2) now -= A0[x], A0[x] = 0;
        if (op == 3) scanf("%d", &y), A0[y] += a[x], now += a[x];
        if (op == 4) now += A[x] - A0[x], A0[x] = A[x];
        if (sum == now) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

