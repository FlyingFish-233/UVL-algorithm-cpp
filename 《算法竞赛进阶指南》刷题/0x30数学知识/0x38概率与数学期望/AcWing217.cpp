# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

int in[NR], deg[NR];
double f[NR];
queue<int> q;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(y, x, w), in[x]++, deg[x]++;
    q.push(n);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            f[y] += (f[x] + g[i].w) / deg[y];
            if (--in[y] == 0) q.push(y);
        }
    }
    printf("%.2f\n", f[1]);
    return 0;
}