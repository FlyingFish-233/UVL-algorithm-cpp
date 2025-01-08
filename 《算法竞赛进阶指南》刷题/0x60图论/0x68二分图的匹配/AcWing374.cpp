# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;
const double eps = 1e-8;

struct Edge
{
    int to, next;
};

int n, m, t1, t2, v;
int nx[NR], ny[NR], mx[NR], my[NR];

double dist(int a, int b)
{
    return sqrt((nx[a] - mx[b]) * (nx[a] - mx[b]) + (ny[a] - my[b]) * (ny[a] - my[b]));
}

int gsz, fte[NR];
Edge g[NR];

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

bool check(double mid)
{
    memset(fte, 0, sizeof(fte)), gsz = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                if (k * (t1 / 60.) + (k - 1) * t2 + dist(j, i) / v <= mid) addEdge(i, (j - 1) * m + k);
                else break;
    memset(opp, 0, sizeof(opp));
    for (int i = 1; i <= m; i++) {
        memset(vis, false, sizeof(vis));
        if (!find(i)) return false;
    }
    return true;
}

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &t1, &t2, &v);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &mx[i], &my[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nx[i], &ny[i]);

    double l = 0, r = 1e5;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%.6f\n", l);
    return 0;
}