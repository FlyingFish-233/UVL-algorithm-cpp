// AcWing10 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 110, MR = 110;

int n, m, root;
int w[NR], v[NR];
vector<int> g[NR];
int f[NR][MR];

void dfs(int x)
{
    for (int j = w[x]; j <= m; j++) f[x][j] = v[x];
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        dfs(y);
        for (int j = m; j >= w[x]; j--)
            for (int k = w[x]; k <= j; k++)
                f[x][j] = max(f[x][j], f[x][k] + f[y][j - k]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d%d%d", &w[i], &v[i], &x);
        if (x == -1) root = i;
        else g[x].push_back(i);
    }
    dfs(root);
    printf("%d\n", f[root][m]);
    return 0;
}