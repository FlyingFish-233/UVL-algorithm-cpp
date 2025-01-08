# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 210, mod = 1e9 + 7;

struct Edge
{
    int to, w;
};

int n, k, m;
vector<Edge> g[NR];
int in[NR], f[NR][2][NR];

void dfs(int x)
{
    if (g[x].size() == 0) { f[x][0][0] = f[x][1][1] = 1; return; }
    int num = g[x].size();
    int f0[NR][NR], f1[NR][NR];
    memset(f0, 0, sizeof(f0)), f0[0][0] = 1;
    memset(f1, 0, sizeof(f1)), f1[0][0] = 1;
    for (int i = 0; i < num; i++) {
        int y = g[x][i].to, w = g[x][i].w; dfs(y);
        for (int j = 0; j <= k; j++)
            for (int l = 0; l <= j; l++) {
                (f0[i + 1][j] += 1ll * f0[i][j - l] * (f[y][0][l] + f[y][1][l]) % mod) %= mod;
                (f1[i + 1][j] += 1ll * f1[i][j - l] * f[y][!w][l] % mod) %= mod;
            }
    }
    for (int i = 0; i <= k; i++) {
        f[x][0][i] = f0[num][i];
        if (i >= 1) f[x][1][i] = f1[num][i - 1];
    }
}

int main()
{
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= m; i++) {
        char c[2]; int x, y;
        scanf("%s%d%d", c, &x, &y), in[y]++;
        g[x].push_back((Edge) {y, c[0] == 'A'});
    }
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) g[0].push_back((Edge) {i, 0});
    dfs(0);
    printf("%d\n", f[0][0][k]);
    return 0;
}

