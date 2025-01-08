# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1010;

struct Edge
{
    int to, next;
};

int n, m, k;
int gsz, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

bool vis[NR];
int opp[NR];

bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (opp[y] == 0 || find(opp[y]))
            { opp[y] = x; return true; }
    }
    return false;
}

int main()
{
    while (scanf("%d", &n) && n) {
        scanf("%d%d", &m, &k);
        memset(fte, 0, sizeof(fte)), gsz = 0;
        for (int i = 1, x, y; i <= k; i++) {
            scanf("%*d%d%d", &x, &y);
            if (x && y) addEdge(x, y);
        }
        memset(opp, 0, sizeof(opp));
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            memset(vis, false, sizeof(vis));
            ans += find(i);
        }
        printf("%d\n", ans);
    }
    return 0;
}