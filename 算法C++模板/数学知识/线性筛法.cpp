// P3383 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e8 + 10;

int n, m, q;
int v[NR], p[NR];

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) v[i] = p[++m] = i;
        for (int j = 1; j <= m && p[j] <= v[i] && i * p[j] <= n; j++)
            v[i * p[j]] = p[j];
    }
    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", p[x]);
    }
    return 0;
}