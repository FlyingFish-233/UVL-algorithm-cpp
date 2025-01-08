// P8817 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2500 + 10, MR = 2e4 + 10;

struct Edge
{
    int to, next;
};

int n, m, k;
long long w[NR];
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

int q[NR], dep[NR];

void mark(int s)
{
    memset(dep, -1, sizeof(dep));
    int l = 1, r = 0;
    q[++r] = s, dep[s] = 0;
    while (l <= r) {
        int x = q[l++];
        if (dep[x] == k + 1) continue;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dep[y] == -1) dep[y] = dep[x] + 1, q[++r] = y;
        }
    }
}

bool G[NR][NR];
long long mx[3][NR];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 2; i <= n; i++)
        scanf("%lld", &w[i]);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), addEdge(x, y);
    for (int i = 1; i <= n; i++) {
        mark(i);
        for (int j = 1; j <= n; j++)
            G[i][j] = (dep[j] >= 0);
    }
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++) if (j != i && G[i][j] && G[1][j]) {
            if (w[j] > w[mx[0][i]]) mx[2][i] = mx[1][i], mx[1][i] = mx[0][i], mx[0][i] = j;
            else if (w[j] > w[mx[1][i]]) mx[2][i] = mx[1][i], mx[1][i] = j;
            else if (w[j] > w[mx[2][i]]) mx[2][i] = j;
        }
    long long ans = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++) if (j != i && G[i][j])
            for (int ti = 0; ti <= 2; ti++) if (mx[ti][i] != 0 && mx[ti][i] != j)
                for (int tj = 0; tj <= 2; tj++) if (mx[tj][j] != 0 && mx[tj][j] != i && mx[ti][i] != mx[tj][j])
                    ans = max(ans, w[i] + w[j] + w[mx[ti][i]] + w[mx[tj][j]]);
    printf("%lld\n", ans);
    return 0;
}