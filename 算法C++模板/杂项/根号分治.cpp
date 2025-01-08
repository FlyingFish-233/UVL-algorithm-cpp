// P3369 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 150000 + 10, MR = 400 + 10;

int n, m, T;
int a[NR];
int f[MR][MR];

int main()
{
    scanf("%d%d", &n, &m), T = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= T; i++)
        for (int j = 1; j <= n; j++)
            f[i][j % i] += a[j];
    while (m--) {
        char op; int x, y;
        cin >> op >> x >> y;
        if (op == 'A') {
            if (x <= T) printf("%d\n", f[x][y]);
            else {
                int ans = 0;
                for (int i = y; i <= n; i += x)
                    ans += a[i];
                printf("%d\n", ans);
            }
        }
        if (op == 'C') {
            for (int i = 1; i <= T; i++)
                f[i][x % i] += y - a[x];
            a[x] = y;
        }
    }
    return 0;
}