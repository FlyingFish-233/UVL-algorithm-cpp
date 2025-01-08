# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, m;
int nxt[NR];

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1, l, r; i <= m; i++)
        scanf("%d%d", &l, &r), nxt[l] = max(nxt[l], r);
    for (int i = 1; i <= n; i++)
        nxt[i] = max(nxt[i], nxt[i - 1]);
    int p = 1, ans = 0;
    while (p <= n && nxt[p] >= p) p = nxt[p] + 1, ans++;
    printf("%d\n", (p <= n) ? -1 : ans);
    return 0;
}