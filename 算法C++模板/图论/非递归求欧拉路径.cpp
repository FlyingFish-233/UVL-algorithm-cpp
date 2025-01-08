# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10, MR = 1e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int gsz = 1, fte[NR], deg[NR];
Edge g[MR];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

int top, st[MR];
bool vis[MR];
int len, ans[MR];

void euler(int s)
{
    st[++top] = s;
    while (top > 0) {
        int x = st[top], i = fte[x];
        while (i && vis[i]) i = g[i].next;
        if (i) st[++top] = g[i].to, vis[i] = vis[i ^ 1] = true, fte[x] = g[i].next;
        else top--, ans[++len] = x;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        addEdge(x, y), addEdge(y, x);
        deg[x]++, deg[y]++;
    }
    int tmp = 0, s = 1;
    for (int i = 1; i <= n; i++)
        if (deg[i] % 2 == 1) tmp++, s = i;
    if (tmp != 0 && tmp != 2) return printf("No\n"), 0;
    euler(s);
    reverse(ans + 1, ans + len + 1);
    for (int i = 1; i <= len; i++)
        printf("%d\n", ans[i]);
    return 0;
}