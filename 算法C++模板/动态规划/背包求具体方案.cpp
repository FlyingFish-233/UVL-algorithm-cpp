// AcWing12 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10, MR = 1e3 + 10;

int n, m;
int w[NR], v[NR];
int f[MR];
bool flag[NR][MR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &w[i], &v[i]);
    for (int i = n; i >= 1; i--) // 字典序最小
        for (int j = m; j >= w[i]; j--)
            if (f[j] <= f[j - w[i]] + v[i]) 
                f[j] = f[j - w[i]] + v[i], flag[i][j] = true;
    for (int i = 1, j = m; i <= n; i++)
        if (flag[i][j]) printf("%d ", i), j -= w[i];
    return 0;
}